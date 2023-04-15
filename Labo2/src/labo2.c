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
#include <avr/interrupt>
#include <stdio.h>

/* Se definen las varibles para las 3 interrupciones*/
int interrupt_1 = 0;
int interrupt_2 = 0;
int interrupt_3 = 0;

int main(void)
{
    //Definición de salidas
    DDRB = 0b00001111; //Configuracion del puerto B, corresponden a salidas, puertos B0,B1,B2 y B3

	// Tambien definir salidas puertos D1, D0 y A2

	// Entradas con interrupciones corresponden a puertos D2, D3 Y D4
	
    GIMSK |= (1<<INT0)|(1<<INT1); // interrupciones externas en D2 y D3

	// Salidas para el display de lesd B7 B6 B5 B4 y D5

}


void delay(int time_delay){
	TIMSK = 0b10;
	enable = 1;
	counter = 0;
	TCNT0= 0x00;
	while(counter <= time_delay){
		PORTB &= 0xFF;
	}
	// Volvemos las variables al valor inicial
	TIMSK = 0b00;
	enable = 0;   
}

/* Definición de led individuales que indican
el estado en el ciclo de trabajo de la lavadora:
suministro de agua, lavar, enjuagar y centrifugar
*/
void green_light(int delay){
    PORTB = 0b00000001;
    delay(200);
    PORTB = 0b00000000; // Lo dejamos en bajo
	delay(200);
}

void yellow_light(int delay){
    PORTB = 0b00000010;
    delay(200);
    PORTB = 0b00000000; // Lo dejamos en bajo
    delay(200);
}

void red_light(int delay){
    PORTB = 0b00000100;
    delay(200);
    PORTB = 0b00000000; // Lo dejamos en bajo
    delay(200);
}

void blue_light(int delay){
    PORTB = 0b00001000;
    delay(200);
    PORTB = 0b00000000; // Lo dejamos en bajo
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