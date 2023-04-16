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

// Definición de estados
#define waiting_user_input 0 // interrupcion

#define start_wash 0 // inicio ciclo de lavado, se define el patron de acuerdo
					 // al ciclo seleccionado, interrupcion del usuario

#define suministro_agua 0 // primer paso del lavado, enciende led correspondiente 
						  // y pasa el tiempo en el display

#define lavar 0// segundo paso, enciende led correspondiente y pasa tiempo en el display

#define enjuagar 0// tercer paso, enciende led correspondiente y pasa tiempo en el display

#define centrifugar 0// cuarto paso, enciende led correspondiente y pasa tiempo en el display

#define checking 0   // revisión de que haya pasado por los 4 estados de lavado:
					 // tiene que encenderse los cuatro leds correspondientes

#define finish 0     // fin del lavado

int main(void)
{
    // Definición de salidas

	/*
	DDRB = Port B Data Direction Register 8 bits
	Configuracion del puerto B: Todos como salidas
	Puertos B0,B1,B2 y B3 *(LEDS)y los leds B7 B6 B5 B4 (Para el decodificador)
	*/
    DDRB = 0b11111111;

	/*
	DDRD = Port D Data Direction Register 7 bits
	Salidas puertos D1, D0
	*/ 
	DDRD = 0b0010011;

	/*
	DDRA = Port A Data Register 3 bits
	*/
	DDRA = 0b010; // A1 como salida

	/*Entradas con interrupciones corresponden a puertos D2, D3 Y D4
	GIMSK = General Interrupt Mask Register */ 
    GIMSK |= (1<<INT0)|(1<<INT1)|(1<<PCIE0); // interrupciones externas en D2 , D3 y D4 (BIT 7, 6 y 5)

	char state = waiting_user_input;
	char next_state = waiting_user_input;

	while(1){

		case(waiting_user_input):
			if ((interrupt_1 == 1) | (interrupt_2 == 1) | (interrupt_3 == 1)){
				interrupt_1 == 0; interrupt_2 == 0; interrupt_3 == 0; // Vuelven a valor inicial
				next_state == start_wash;
			}
			else{
				next_state == waiting_user_input; // se sigue esperando la entrada del usuario
			}
		
		break;

		case(start_wash): 
			if(interrupt_1 == 1){ // Interrupt 1 = Baja
				interrupt_1 ==0;
				green_light_charge(delay) // Indica que es un lavado con carga baja
				// Indicar valores del tiempo para cada etapa ??
				next_state == suministro_agua;

			}

			else if(interrupt_2 == 1){ // Interrupt 2 = Media
				interrupt_2 ==0;
				yellow_light_charge(delay) // Indica que es un lavado con carga media
				next_state == suministro_agua;

			}

			else if(interrupt_3 == 1){ // Interrupt 2 = Media
				interrupt_3 ==0;
				red_light_charge(delay) // Indica que es un lavado con carga media
				next_state == suministro_agua;

			}

			else{
				next_state == start_wash;
			}
		break;

		case(suministro_agua):
			green_light(delay);
			next_state == lavar;
		break;

		case(lavar):
			yellow_light(delay);
			next_state == enjuagar;
		break;
		
		case(centrifugar):
			blue_light(delay);
			next_state == checking;
		break;

		case(checking): 
			// revisar si se paso por los 4 estados de lavado
			// no se si sea necesario porque para llegar aqui tuvo que jaja
		break;
		
		case(finish); 
		break;
	}

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

/* Definición de leds individuales para indicar
el nivel de carga 
*/

void green_light_charge(int time_delay){
    PORTD = 0b0000001;
    delay(200);
    PORTD = 0b0000000; // Lo dejamos en bajo
	delay(200);
}

void yellow_light_charge(int time_delay){
    PORTD = 0b0000010;
    delay(200);
    PORTD = 0b0000000; // Lo dejamos en bajo
    delay(200);
}

void red_light_charge(int time_delay){
    PORTA = 0b010;
    delay(200);
    PORTA = 0b000; // Lo dejamos en bajo
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