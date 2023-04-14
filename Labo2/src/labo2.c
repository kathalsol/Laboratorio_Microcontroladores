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
int delay = 100;

int main(void)
{
    
}


/* Definición de led individuales que indican
el estado en el ciclo de trabajo de la lavadora:
suministro de agua, lavar, enjuagar y centrifugar
*/
void green_light(int delay){
    PORTB = 0b00000001;
    // definir delay
    PORTB = 0b00000000; // Lo dejamos en bajo
    // delay
}

void yellow_light(int delay){
    PORTB = 0b00000010;
    // definir delay
    PORTB = 0b00000000; // Lo dejamos en bajo
    // delay
}

void red_light(int delay){
    PORTB = 0b00000100;
    // definir delay
    PORTB = 0b00000000; // Lo dejamos en bajo
    // delay
}

void blue_light(int delay){
    PORTB = 0b00001000;
    // definir delay
    PORTB = 0b00000000; // Lo dejamos en bajo
    // delay
}

/* Función que muestra debidamente los números en cada display*/
// Corregir lo de GPIO para este caso
void led_display(int valor, int display)
{
    if (display == 0)
	{
		if (valor == 0) GPIO = 0b00000000;

		else if (valor == 1) GPIO = 0b00000001; 

		else if (valor == 2) GPIO = 0b00000010; 

		else if (valor == 3) GPIO = 0b00000011;

		else if (valor == 4) GPIO = 0b00000100;

		else if (valor == 5) GPIO = 0b00000101;

		else if (valor == 6) GPIO = 0b00000110;

		else if (valor == 7) GPIO = 0b00000111;

		else if (valor == 8) GPIO = 0b00010000;

		else GPIO = 0b00010001;
	}

	else  // display == 1
	{
		if (valor == 0) GPIO = 0b00100000;

		else if (valor == 1) GPIO = 0b00100001; 

		else if (valor == 2) GPIO = 0b00100010; 

		else if (valor == 3) GPIO = 0b00100011;

		else if (valor == 4) GPIO = 0b00100100;

		else if (valor == 5) GPIO = 0b00100101;

		else if (valor == 6) GPIO = 0b00100110;

		else if (valor == 7) GPIO = 0b00100111;

		else if (valor == 8) GPIO = 0b00110000;

		else GPIO = 0b00110001;
	}
}