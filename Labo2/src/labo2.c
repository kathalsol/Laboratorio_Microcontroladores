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

/* Se definen las varibles para las 3 interrupciones*/
int counter, enable, state, wash_state, next_wash_state, load_state;
int time_delay = 100;

// Definición de estados

#define waiting_user_input 0 

#define low_load 1 //carga baja

#define medium_load 2 // carga media

#define high_load 3 // carga alta

#define stop_wash 4

#define start_wash 5 // inicio ciclo de lavado, se define el patron de acuerdo
					 // al ciclo seleccionado, interrupcion del usuario

#define suministro_agua 6 // primer paso del lavado, enciende led correspondiente 
						  // y pasa el tiempo en el display

#define lavar 7 // segundo paso, enciende led correspondiente y pasa tiempo en el display

#define enjuagar 8 // tercer paso, enciende led correspondiente y pasa tiempo en el display

#define centrifugar 9 // cuarto paso, enciende led correspondiente y pasa tiempo en el display

#define finish 10  // fin del ciclo de lavado

//Declaracion de funciones
void setup();
void delay(int time_delay);
void green_light(int time_delay);
void yellow_light(int time_delay);
void red_light(int time_delay);
void green_light_load(int time_delay);
void yellow_light_load(int time_delay);
void red_light_load(int time_delay);


int main(void)
{
    setup();

	char state = waiting_user_input;
	char wash_state = waiting_user_input;
	char load_state= waiting_user_input;
	char next_wash_state = waiting_user_input;
	while(1){
		switch(load_state){
			case(low_load):
				green_light_load(time_delay);

			break;
			case(medium_load):
				yellow_light_load(time_delay);
		
			break;
			case(high_load):
				red_light_load(time_delay);

			break;
		}

		switch(wash_state){
			case(suministro_agua):
				if(load_state == low_load){
					//Definen valores de los tiempos
				}
				else if(load_state == medium_load){

				}
				else if(load_state == high_load){

				}
			break;
			case(lavar):
				if(load_state == low_load){
					
				}
				else if(load_state == medium_load){

				}
				else if(load_state == high_load){

				}
			break;
			case(enjuagar):
				if(load_state == low_load){
					
				}
				else if(load_state == medium_load){

				}
				else if(load_state == high_load){

				}
			break;
			case(centrifugar):
					if(load_state == low_load){
						
					}
					else if(load_state == medium_load){

					}
					else if(load_state == high_load){

					}
			break;
			case(finish):
			break;
		}

		switch(state){
			wash_state = next_wash_state;
			case(start_wash):
				wash_state = suministro_agua;
				if(wash_state == suministro_agua){
					next_wash_state = lavar;
				}
				else if(wash_state == lavar){
					next_wash_state = enjuagar;
				}
				else if(wash_state == enjuagar){
					next_wash_state = centrifugar;
				}
				else if(wash_state == centrifugar){
					next_wash_state = finish;
				}
				else{
					state = start_wash;
				}
			break;
			case(stop_wash):
			break;
		}

	}
		
}

ISR(INT0_vect) //Boton pausa
{

	state = stop_wash;
}

ISR(INT1_vect) //Boton start
{

	state = start_wash;
}

ISR(PCINT0_vect) {
	//Interupcion carga baja
	state = low_load;

}
ISR(PCINT1_vect) {
	state = medium_load;
}
ISR(PCINT2_vect) {
	state = high_load;
} 

/*ISR(PCINT0_vect) 
{
	if (bit_is_set(PINB, PB0)) {
		load_state = low_load;
	}
	if (bit_is_set(PINB, PB1)) {
		load_state = medium_load;
	}
	if (bit_is_set(PINB, PB2)) {
		load_state = high_load;
	}
}*/


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
    DDRB = 0b11111111; 
	DDRD = 0b0111000;
	DDRA = 0b000;

	// configurar GIMSK 
	GIMSK |= (1<<PCIE0) | (1 << INT0) | (1 << INT1);

	//Configurar INT0 e INT1 por flanco positivo EICRA (deafult positivo creo)

	PCMSK |= (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2); // Interrupciones de los niveles de carga
    
	
	// Habilitar interrupciones globales
    sei();
}

void delay(int time_delay){
	TIMSK = 0b10;
	enable = 1;
	counter = 0;
	TCNT0= 0x00;
	while(counter <= time_delay){
		PORTD &= 0xFF;
	}
	// Volvemos las variables al valor inicial
	TIMSK = 0b00;
	enable = 0;   
}

/* Definición de led individuales que indican
el estado en el ciclo de trabajo de la lavadora:
suministro de agua, lavar, enjuagar y centrifugar

void green_light(int time_delay){
    PORTB = 0b00000001;
    delay(200);
    PORTB = 0b00000000; // Lo dejamos en bajo
	delay(200);
}

void yellow_light(int time_delay){
    PORTB = 0b00000010;
    delay(200);
    PORTB = 0b00000000; // Lo dejamos en bajo
    delay(200);
}

void red_light(int time_delay){
    PORTB = 0b00000100;
    delay(200);
    PORTB = 0b00000000; // Lo dejamos en bajo
    delay(200);
}

void blue_light(int time_delay){
    PORTB = 0b00001000;
    delay(200);
    PORTB = 0b00000000; // Lo dejamos en bajo
    delay(200);
}
*/

/* Definición de leds individuales para indicar
el nivel de carga 
*/

void green_light_load(int time_delay){
    PORTD = 0b0001000;
    delay(200);
    PORTD = 0b0000000; // Lo dejamos en bajo
	delay(200);
}

void yellow_light_load(int time_delay){
    PORTD = 0b0010000;
    delay(200);
    PORTD = 0b0000000; // Lo dejamos en bajo
    delay(200);
}

void red_light_load(int time_delay){
    PORTD = 0b0100000;
    delay(200);
    PORTD = 0b0000000;// Lo dejamos en bajo
    delay(200);
}

/* Función que muestra debidamente los números en cada display*/
// Corregir lo de GPIO para este caso
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