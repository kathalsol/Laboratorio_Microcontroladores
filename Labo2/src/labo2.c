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
#define STOP_BUTTON (1<<PD2)
#define START_BUTTON (1<<PD3)
#define MEDIUM_LOAD_BUTTON (1<<PD6)
#define LOW_LOAD_BUTTON (1<<PB0)
#define HIGH_LOAD_BUTTON (1<<PA0)
#define LED_LOW_LOAD (1<<PD0)
#define LED_MEDIUM_LOAD (1<<PD1)
#define LED_HIGH_LOAD (1<<PA1)


//Definicion de estados
typedef enum {
	STATE_IDEL,
	STATE_START_WASH,
	STATE_STOP_WASH,
	STATE_WATER_SUPPLY,
	STATE_WASH,
	STATE_RISE,
	STATE_SPIN,
	STATE_FINISH
} state_t;


// Se definen las varibles globales
volatile state_t state = STATE_IDEL;
volatile uint8_t load = 0;

//Declaracion de funciones
void setup();
void delay_ms(uint16_t ms);


int main(void)
{
    setup();
	while(1){

	}
	return 0;
}

ISR(INT0_vect) //Boton pausa
{
	//state = stop_wash;
	if(PIND & STOP_BUTTON){
		state = STATE_IDEL;
	}
	else{

	}
}

ISR(INT1_vect) //Boton start
{
	if(PIND & START_BUTTON){
		state = STATE_START_WASH;
	}
	else {

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




void setup()
/* Definición de entradas y salidas
   - DDRB: Port B Data Direction Register 8 bits
	Configuracion del puerto B: Todos como salidas
	Puertos B0,B1,B2 y B3 *(LEDS)y los leds B7 B6 B5 B4 (Para el decodificador)
   - DDRD: Port D Data Direction Register 7 bits
	Salidas puertos D1 y D5, D0 como entrada
   - DDRA: Port A Data Register 3 bits
	A1 y A0 como salida
   - PCMSK0 y PCMSK1 : Pin change mask register 0 and 1
	Utilizados para definir en que puertos I/O estan las interrupciones
	D2, D3 Y D4, además de D0 y D6
*/
{

	//Configuras los pines como entrada
	DDRB &= ~LOW_LOAD_BUTTON;
	DDRA &= ~HIGH_LOAD_BUTTON;
	DDRD &= ~(MEDIUM_LOAD_BUTTON | STOP_BUTTON | START_BUTTON);
	//Configuras los pines como salida
	DDRD |= (LED_MEDIUM_LOAD | LED_LOW_LOAD);
	DDRA |=	LED_HIGH_LOAD;

	// Habilitar pull-up en botones
    PORTD |= (START_BUTTON | STOP_BUTTON | MEDIUM_LOAD_BUTTON);
	PORTB |= LOW_LOAD_BUTTON; 
	PORTA |= HIGH_LOAD_BUTTON;

	//Configucion registro PCMSK para activar interupciones
	PCMSK |= (1<<PCINT0); // Interrupcion carga baja B0

	PCMSK1 |= (1<<PCINT8); // Interrupcion nivel alta A0
    
	PCMSK2 |= (1<<PCINT17); //Interrupcion nivel media D6

	//Configuracion GIMSK para activar interupciones
	GIMSK |= ((1<<PCIE0) | (1<<PCIE1) | (1<<PCIE2)); //Interupciones de los botones de carga
	GIMSK |= (1 << INT0) | (1 << INT1); // Interrupcion de inicio y final

	//MCUCR |= (1<<ISC01) | (1<<ISC00); // LA INTERRUPCION SE DETECTARA EN LOS FLANCOS POSITIVOS.
	
	
	// Habilitar interrupciones globales
    sei();
}

void delay_ms(uint16_t ms) {
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

/*
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
*/