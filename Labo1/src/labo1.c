#include <pic14/pic12f683.h>

void delay (unsigned tiempo);
unsigned int get_rand(unsigned int min, unsigned int max);
void led_display(int valor, int display);

void main(void)
{


}

/* Función que genera los números aleatorios*/
unsigned int get_rand(unsigned int min, unsigned int max)
{
    static unsigned int rand = 0x1A56; /*Valor inicial*/

    rand += ((rand * rand) /10) % 9899;

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

	else if (display == 1)
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

void delay(unsigned int tiempo)
{
	unsigned int i;
	unsigned int j;

	for(i=0;i<tiempo;i++)
	  for(j=0;j<1275;j++);
}