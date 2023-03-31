#include <pic14/pic12f683.h>

/* Configuración de registro CONFIG, se desabilita el WDT y
el inicio por defecto de GP3 como MCLRE(RESET)*/
typedef unsigned int word;
word __at 0x2007 __CONFIG = (_WDTE_OFF & _WDT_OFF & _MCLRE_OFF);

void delay (unsigned tiempo);
unsigned int get_rand(unsigned int min, unsigned int max);
void led_display(int valor, int display);

void main(void)
{
	TRISIO = 0b00001000; // Poner todos los pines como salidas, GP3 como entrada por default
	GPIO = 0x00; //Poner pines en bajo

	unsigned int time = 10;
	unsigned int numero1, numero2;
	unsigned int contador = 0;

	//Loop forever
	while( 1 )
	{
		// Se obtienen los dos números aleatorios
		numero1 = get_rand(0,9);
		numero2 = get_rand(0,9);

		/* Cuando el boton NO está presionado se generan 
		los números aleatorios */
		led_display(numero1, 0);
		delay(time);
		led_display(numero2, 1);
		delay(time);

		contador = contador + 1;

		/* Si se han generado 16 numeros diferentes entonces
		se muestra el numero 9 en el display 0 y 9 en el 
		display 1 generando un 99 intermitente */
		if (contador == 16)
		{
			led_display(9, 0);
			delay(time);
			led_display(9, 1);
			delay(time);
			led_display(9, 0);
			delay(time);
			led_display(9, 1);
			delay(time);
			led_display(9, 0);
			delay(time);
			led_display(9, 1);
			delay(time);
			led_display(9, 0);
			delay(time);
			led_display(9, 1);
			delay(time);
			/* Se reinicia el contador cada vez que cuenta a 16 hasta que
			se terminan los 99 números posibles */
			contador = 0;
		}

		if(GP3)  // Cuando el botón está presionado (configuración pull down)
		{
			while (GP3)
			{
				led_display(numero1, 0);
				delay(time);
				led_display(numero2, 1);
				delay(time);

			}
		}
	}
}

/* Función que genera los números aleatorios*/
unsigned int get_rand(unsigned int min, unsigned int max)
{
    static unsigned int rand = 999; /*Valor inicial*/

    rand += ((rand * rand) /100) % 10000;

    return rand % (max+1-min)+min;

}

/* Función que muestra debidamente los números en cada display*/
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

/* Función de atraso - delay*/
void delay(unsigned int tiempo)
{
	unsigned int i;
	unsigned int j;

	for(i=0;i<tiempo;i++)
	  for(j=0;j<1275;j++);
}
