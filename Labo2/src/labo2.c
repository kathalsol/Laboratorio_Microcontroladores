/* 
   Universidad de Costa Rica
   Laboratorio de Microcontroladores
   Laboratorio 2 - Lavadora automática
   Estudiantes:  
    - Katharina Alfaro Solís B80251
    - Mauricio Rodríguez Obando B96694
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

//Definicion de pines
#define RESET_BUTTON (1<<PD2)
#define START_PAUSE_BUTTON (1<<PD3)
#define MEDIUM_LOAD_BUTTON (1<<PD6)
#define LOW_LOAD_BUTTON (1<<PB0)
#define HIGH_LOAD_BUTTON (1<<PA0)
#define LED_LOW_LOAD (1<<PD0)
#define LED_MEDIUM_LOAD (1<<PD1)
#define LED_HIGH_LOAD (1<<PA1)
#define LED_START_PAUSE (1<<PB1)
#define LED_STATE_WATER_SUPPLY (1<<PA2)
#define LED_STATE_WASH (1<<PD4)
#define LED_STATE_RISE (1<<PD5)
#define LED_STATE_SPIN (1<<PB7)

//Definicion de estados
typedef enum {
	STATE_IDEL,
	STATE_WATER_SUPPLY,
	STATE_WASH,
	STATE_RISE,
	STATE_SPIN,
	STATE_FINISH
} state_t;


// Se definen las varibles globales
volatile state_t state = STATE_IDEL;
volatile state_t next_state = STATE_IDEL;
volatile uint8_t load = 0;
volatile uint8_t compare_value = 0;
volatile uint8_t time = 0, time_left = 0;

//Declaracion de funciones
void setup();
void setup_timer0(uint8_t compare_value);
void delay_ms(uint16_t ms);
void fsm();
int water_supply(uint8_t load);
int wash(uint8_t load);
int rise(uint8_t load);
int spin(uint8_t load);
void finish(uint8_t load);
void led_display(int valor, int display);



int main(void)
{
    setup();
	setup_timer0(compare_value);
	while(1){
		fsm();
	}
	return 0;
}

ISR(INT0_vect) //Boton reset
{
	//state = stop_wash;
	if(PIND & RESET_BUTTON){
		state = STATE_IDEL;
	}
}

ISR(INT1_vect) //Boton start/pause
{
	if(PIND & START_PAUSE_BUTTON){
		//Cuando el timer esta activado se detiene
		if (TIMSK & (1<<TOIE0)){
			TIMSK &= ~(1<<TOIE0);
			PORTB &= ~LED_START_PAUSE;
		}
		//Si esta detenido lo iniciamos
		else{
			TIMSK |= (1<<TOIE0);
			PORTB |= LED_START_PAUSE;
		}
		
	}
}

ISR(PCINT0_vect)//Interupcion carga baja 
{
	if(PINB & LOW_LOAD_BUTTON){
		load = 1;
		PORTD |= LED_LOW_LOAD;
	}
	else {
		PORTD &= ~LED_LOW_LOAD;
	}

}
ISR(PCINT2_vect) //Interupcion carga media
{
	if(PIND & MEDIUM_LOAD_BUTTON){
		load = 2;
		PORTD |= LED_MEDIUM_LOAD;
	}
	else {
		PORTD &= ~LED_MEDIUM_LOAD;
	}

}
ISR(PCINT1_vect) //Interupcion carga alta
{
	if(PINA & HIGH_LOAD_BUTTON){
		load = 3;
		PORTA |= LED_HIGH_LOAD;
	}
	else {
		PORTA &= ~LED_HIGH_LOAD;
	}
}

ISR(TIMER0_COMPA_vect) {
  // Aqui va la rutina de interrupcion
  // Hacer LED display cada vez que se produzca la interrupción
	static uint8_t contador = 0;
	contador++;
	 
	// Se configuró el timer0 con un prescales de 64 y reloj de 1 MHz
	// Se ocupan 15625 ciclos del timer para que pase un segundo
	if(contador == 15625){
		time++;
		time_left--;
		//led_display()
	}
	else if(time == compare_value){
		//led_display(0,0)
		TCNT0 = 0;
		TIMSK &= ~(1<<TOIE0);
	}
	contador = 0;
}

_

void setup()
{

	//Configuras los pines como entrada
	DDRB &= ~LOW_LOAD_BUTTON;
	DDRA &= ~HIGH_LOAD_BUTTON;
	DDRD &= ~(MEDIUM_LOAD_BUTTON | RESET_BUTTON | START_PAUSE_BUTTON);
	//Configuras los pines como salida
	DDRD |= (LED_MEDIUM_LOAD | LED_LOW_LOAD | LED_STATE_WASH | LED_STATE_RISE);
	DDRB |= (LED_START_PAUSE | LED_STATE_SPIN);
	DDRA |=	(LED_HIGH_LOAD | LED_STATE_WATER_SUPPLY); //revisar como poner como salida pin A2

	// Habilitar pull-up en botones
    PORTD |= (START_PAUSE_BUTTON | RESET_BUTTON | MEDIUM_LOAD_BUTTON);
	PORTB |= LOW_LOAD_BUTTON; 
	PORTA |= HIGH_LOAD_BUTTON;

	//Configucion registro PCMSK para activar interupciones
	PCMSK |= (1<<PCINT0); // Interrupcion carga baja B0

	PCMSK1 |= (1<<PCINT8); // Interrupcion nivel alta A0
    
	PCMSK2 |= (1<<PCINT17); //Interrupcion nivel media D6

	//Configuracion GIMSK para activar interupciones
	GIMSK |= ((1<<PCIE0) | (1<<PCIE1) | (1<<PCIE2)); //Interupciones de los botones de carga
	GIMSK |= ((1 << INT0) | (1 << INT1)); // Interrupcion de start/pause y reset

	//MCUCR |= (1<<ISC01) | (1<<ISC00); // LA INTERRUPCION SE DETECTARA EN LOS FLANCOS POSITIVOS.
	
}

void setup_timer0(uint8_t compare_value)
{
	// Configurar el prescaler a 64
	TCCR0B |= (1 << CS01) | (1 << CS00);

	// Definir el valor de comparación
	OCR0A = compare_value; //15624 si es cada 1s para el prescaler de 64 y un reloj de 1MHz

	// Configuracion del modo de operacion CTC
	TCCR0A |= (1 << WGM01);

	// Habilitar la interrupción de comparación en la salida A
  	TIMSK |= (1 << OCIE0A);

	// Se habilitan interrupciones globales
	sei();
}

void fsm()
{	
	state = next_state;
	switch (state)
	{
	case STATE_IDEL:
		next_state = STATE_WATER_SUPPLY; 
		break;	
	case STATE_WATER_SUPPLY:
		water_supply(load);
		next_state = STATE_WASH;
		break;
	case STATE_WASH:
		wash(load);
		next_state = STATE_RISE;
		break;
	case STATE_RISE:
		rise(load);
		next_state = STATE_SPIN;
		break;
	case STATE_SPIN:
		spin(load);
		next_state = STATE_FINISH;
		break;
	case STATE_FINISH:
		finish(load);
		break;
	default:

	}
}

void delay_ms(uint16_t ms) 
{
    uint16_t count = 256 - ((F_CPU / 64) / 1000);

    while (ms > 0) {
        TCCR0A = 0x00;  // Modo normal
        TCCR0B = 0x03;  // Preescalador de 64
        TIMSK = 0x01;  // Habilitar interrupción de desbordamiento
        TCNT0 = count;  // Cargar valor inicial

        // Esperar a que se complete el retardo
        while ((TIFR & 0x01) == 0);
        TIFR = 0x01;   // Borrar bandera de interrupción

        ms--;
    }
}

int water_supply(uint8_t load)
{	
	PORTA |= LED_STATE_WATER_SUPPLY;
	PORTD &= ~(LED_STATE_WASH | LED_STATE_RISE );
	PORTB &= ~LED_STATE_SPIN;
	
	if (load == 1){
		compare_value = 1;
		delay_ms(100);
		led_display(0,compare_value);
		delay_ms(100);
	}
	else if (load == 2){
		compare_value = 2;
		delay_ms(100);
		led_display(0,compare_value);
		delay_ms(100);
	}
	else if (load == 3){
		compare_value = 3;
		delay_ms(100);
		led_display(0,compare_value);
		delay_ms(100);
	}

	return compare_value;
}

int wash(uint8_t load)
{	
	PORTD |= LED_STATE_WASH;
	PORTD &= ~LED_STATE_RISE ;
	PORTA &= ~LED_STATE_WATER_SUPPLY;
	PORTB &= ~LED_STATE_SPIN;
	
	if (load == 1){
		compare_value = 3;
		delay_ms(100);
		led_display(0,compare_value);
		delay_ms(100);
	}
	else if (load == 2){
		compare_value = 7;
		delay_ms(100);
		led_display(0,compare_value);
		delay_ms(100);
	}
	else if (load == 3){
		compare_value = 10;
		delay_ms(100);
		led_display(1,0);
		delay_ms(100);
	}

	return compare_value;
}

int rise(uint8_t load)
{	
	PORTD |= LED_STATE_RISE;
	PORTA &= ~LED_STATE_WATER_SUPPLY;
	PORTD &= ~LED_STATE_WASH;
	PORTB &= ~LED_STATE_SPIN;
	
	if (load == 1){
		compare_value = 2;
		delay_ms(100);
		led_display(0,compare_value);
		delay_ms(100);
	}
	else if (load == 2){
		compare_value = 4;
		delay_ms(100);
		led_display(0,compare_value);
		delay_ms(100);
	}
	else if (load == 3){
		compare_value = 5;
		delay_ms(100);
		led_display(0,compare_value);
		delay_ms(100);
	}

	return compare_value;
}

int spin(uint8_t load)
{	
	PORTB |= LED_STATE_SPIN;
	PORTD &= ~(LED_STATE_WASH | LED_STATE_RISE);
	PORTA &= ~LED_STATE_WATER_SUPPLY;
	
	if (load == 1){
		compare_value = 3;
		delay_ms(100);
		led_display(0,compare_value);
		delay_ms(100);
	}
	else if (load == 2){
		compare_value = 6;
		delay_ms(100);
		led_display(0,compare_value);
		delay_ms(100);
	}
	else if (load == 3){
		compare_value = 9;
		delay_ms(100);
		led_display(0,compare_value);
		delay_ms(100);
	}

	return compare_value;
}

void finish(uint8_t load)
{	
	// Como final se ponen todas las leds de los estados de lavado en alto 
	PORTD |= LED_STATE_RISE;
	PORTA |= LED_STATE_WATER_SUPPLY;
	PORTD |= LED_STATE_WASH;
	PORTB |= LED_STATE_SPIN;
}

void led_display(int valor, int display)
{
    if (display == 0)
	{
		if (valor == 0) PORTB = 0b00000000;

		else if (valor == 1) PORTB = 0b00000001; 

		else if (valor == 2) PORTB = 0b00000010; 

		else if (valor == 3) PORTB = 0b00000011;

		else if (valor == 4) PORTB = 0b00000100;

		else if (valor == 5) PORTB = 0b00000101;

		else if (valor == 6) PORTB = 0b00000110;

		else if (valor == 7) PORTB = 0b00000111;

		else if (valor == 8) PORTB = 0b00010000;

		else PORTB = 0b00010001;
	}

	else  // display == 1
	{
		if (valor == 0) PORTB = 0b00100000;

		else if (valor == 1) PORTB = 0b00100001; 

		else if (valor == 2) PORTB = 0b00100010; 

		else if (valor == 3) PORTB = 0b00100011;

		else if (valor == 4) PORTB = 0b00100100;

		else if (valor == 5) PORTB = 0b00100101;

		else if (valor == 6) PORTB = 0b00100110;

		else if (valor == 7) PORTB = 0b00100111;

		else if (valor == 8) PORTB = 0b00110000;

		else PORTB = 0b00110001;
	}
}
