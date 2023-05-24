/* 
   Universidad de Costa Rica
   Laboratorio de Microcontroladores
   Laboratorio 4 - Sismografo
   Estudiantes:  
    - Katharina Alfaro Solís B80251
    - Mauricio Rodríguez Obando B96694
*/


// Declaración de bibliotecas y documentos necesarios
// Muchos de estos fueron tomados de los ejemplos de libopencm3
// que se utilizan de base para el desarrollo de este laboratorio

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/nvic.h>
#include "clock.h"
#include "console.h"
#include "sdram.h"
#include "lcd-spi.h"
#include "gfx.h"

// Para el giroscopio se utilizó como base tanto el ejemplo de
// la libreria stm32/f3/stm32-discovery/spi y de stm32/f4/stm.../spi
#define GYR_RNW			(1 << 7) /* Escribe cuando es 0*/
#define GYR_MNS			(1 << 6) /* Multiples lecturas cuando es 1 */
#define GYR_WHO_AM_I		0x0F
#define GYR_OUT_TEMP		0x26
#define GYR_STATUS_REG		0x27
#define GYR_CTRL_REG1		0x20
#define GYR_CTRL_REG1_PD	(1 << 3)
#define GYR_CTRL_REG1_XEN	(1 << 1)
#define GYR_CTRL_REG1_YEN	(1 << 0)
#define GYR_CTRL_REG1_ZEN	(1 << 2)
#define GYR_CTRL_REG1_BW_SHIFT	4
#define GYR_CTRL_REG4		0x23
#define GYR_CTRL_REG4_FS_SHIFT	4

// Se definen para todos los ejes X, Y, Z
#define GYR_OUT_X_L		0x28
#define GYR_OUT_X_H		0x29
#define GYR_OUT_Y_L		0x2A
#define GYR_OUT_Y_H		0x2B
#define GYR_OUT_Z_L		0x2C
#define GYR_OUT_Z_H		0x2D

// Parámetros para la pantalla
#define L3GD20_SENSITIVITY_250DPS  (0.00875F)      
#define L3GD20_SENSITIVITY_500DPS  (0.0175F)       
#define L3GD20_SENSITIVITY_2000DPS (0.070F)        
#define L3GD20_DPS_TO_RADS         (0.017453293F) 

// Declaración de funciones
static void spi_setup(void);
void input_setup(void);
static void adc_setup(void);
static uint16_t read_adc_naiive(uint8_t channel);
gyro getting_xyz(void);

// Variable global para la transmisión
int transmision_enable = 0;

typedef struct Gyro {
  int16_t x;
  int16_t y;
  int16_t z;
} gyro;

static void spi_setup(void){

    // Periféricos del reloj
    rcc_periph_clock_enable(RCC_SPI5);
	/* For spi signal pins */
	rcc_periph_clock_enable(RCC_GPIOC);
	/* For spi mode select on the l3gd20 */
	rcc_periph_clock_enable(RCC_GPIOF);

    // GPIO
    /* Setup GPIOE3 pin for spi mode l3gd20 select. */
	gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO1);
	/* Start with spi communication disabled */
	gpio_set(GPIOC, GPIO1);

	/* Setup GPIO pins for AF5 for SPI1 signals. */
	gpio_mode_setup(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE,
			GPIO7 | GPIO8 | GPIO9);
	gpio_set_af(GPIOF, GPIO_AF5, GPIO7 | GPIO8 | GPIO9);

	//spi initialization
	spi_set_master_mode(SPI15);
	spi_set_baudrate_prescaler(SPI15, SPI_CR1_BR_FPCLK_DIV_64);
	spi_set_clock_polarity_0(SPI15);
	spi_set_clock_phase_0(SPI15);
	spi_set_full_duplex_mode(SPI15);
	spi_set_unidirectional_mode(SPI15); /* bidirectional but in 3-wire */
	spi_enable_software_slave_management(SPI15);
	spi_send_msb_first(SPI15);
	spi_set_nss_high(SPI15);

	//spi_enable_ss_output(SPI15);
	SPI_I2SCFGR(SPI15) &= ~SPI_I2SCFGR_I2SMOD;
	spi_enable(SPI15);

    gpio_clear(GPIOC, GPIO1);
	spi_send(SPI5, GYR_CTRL_REG1); 
	spi_read(SPI5);
	spi_send(SPI5, GYR_CTRL_REG1_PD | GYR_CTRL_REG1_XEN |
			GYR_CTRL_REG1_YEN | GYR_CTRL_REG1_ZEN |
			(3 << GYR_CTRL_REG1_BW_SHIFT));
	spi_read(SPI5);
	gpio_set(GPIOC, GPIO1); 

    gpio_clear(GPIOC, GPIO1);
	spi_send(SPI5, GYR_CTRL_REG4);
	spi_read(SPI5);
	spi_send(SPI5, (1 << GYR_CTRL_REG4_FS_SHIFT));
	spi_read(SPI5);
	gpio_set(GPIOC, GPIO1);
}

void input_setup(void){
    /* Enable GPIOA clock. */
	rcc_periph_clock_enable(RCC_GPIOA);

    /* Enable GPIOG clock. */
	rcc_periph_clock_enable(RCC_GPIOG);

	/* Set GPIO0 (in GPIO port A) to 'input open-drain'. */
	gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO0);

    /* Set GPIO13 (in GPIO port G) to 'output push-pull'. LED PG13 */
	gpio_mode_setup(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);

	/* Set GPIO14 (in GPIO port G) to 'output push-pull'. LED EMERGENCIA */
	gpio_mode_setup(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO14);
}

// Utilizando como base el ejemplo 
// /libopencm3-examples/examples/stm32/f4/stm32f429i-discovery/adc-dac-printf/adc-dac-printf.c

static void adc_setup(void){
    gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO3);
	adc_power_off(ADC1);
	adc_disable_scan_mode(ADC1);
	adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_3CYC);
	adc_power_on(ADC1);
}

static uint16_t read_adc_naiive(uint8_t channel){
	uint8_t channel_array[16];
	channel_array[0] = channel;
	adc_set_regular_sequence(ADC1, 1, channel_array);
	adc_start_conversion_regular(ADC1);
	while (!adc_eoc(ADC1));
	uint16_t reg16 = adc_read_regular(ADC1);
	return reg16;
}

// Funcion que lee las coordenadas xyz del giroscopio
gyro getting_xyz(void)
{
	gyro lectura;
	gpio_clear(GPIOC, GPIO1);
	spi_send(SPI5, GYR_WHO_AM_I | 0x80);
	spi_read(SPI5);
	spi_send(SPI5, 0);
	spi_read(SPI5);
	gpio_set(GPIOC, GPIO1);

	gpio_clear(GPIOC, GPIO1);
	spi_send(SPI5, GYR_STATUS_REG | GYR_RNW);
	spi_read(SPI5);
	spi_send(SPI5, 0);
	spi_read(SPI5);
	gpio_set(GPIOC, GPIO1);

	gpio_clear(GPIOC, GPIO1);
	spi_send(SPI5, GYR_OUT_TEMP | GYR_RNW);
	spi_read(SPI5);
	spi_send(SPI5, 0);
	spi_read(SPI5);
	gpio_set(GPIOC, GPIO1);

	gpio_clear(GPIOC, GPIO1);
	spi_send(SPI5, GYR_OUT_X_L | GYR_RNW);
	spi_read(SPI5);
	spi_send(SPI5, 0);
	lectura.x = spi_read(SPI5);
	gpio_set(GPIOC, GPIO1);

	gpio_clear(GPIOC, GPIO1);
	spi_send(SPI5, GYR_OUT_X_H | GYR_RNW);
	spi_read(SPI5);
	spi_send(SPI5, 0);
	lectura.x |=spi_read(SPI5) << 8;
	gpio_set(GPIOC, GPIO1);

	gpio_clear(GPIOC, GPIO1);
	spi_send(SPI5, GYR_OUT_Y_L | GYR_RNW);
	spi_read(SPI5);
	spi_send(SPI5, 0);
	lectura.y =spi_read(SPI5);
	gpio_set(GPIOC, GPIO1);

	gpio_clear(GPIOC, GPIO1);
	spi_send(SPI5, GYR_OUT_Y_H | GYR_RNW);
	spi_read(SPI5);
	spi_send(SPI5, 0);
	lectura.y|=spi_read(SPI5) << 8;
	gpio_set(GPIOC, GPIO1);

	gpio_clear(GPIOC, GPIO1);
	spi_send(SPI5, GYR_OUT_Z_L | GYR_RNW);
	spi_read(SPI5);
	spi_send(SPI5, 0);
	lectura.z=spi_read(SPI5);
	gpio_set(GPIOC, GPIO1);

	gpio_clear(GPIOC, GPIO1);
	spi_send(SPI5, GYR_OUT_Z_H | GYR_RNW);
	spi_read(SPI5);
	spi_send(SPI5, 0);
	lectura.z|=spi_read(SPI5) << 8;
	gpio_set(GPIOC, GPIO1);

	lectura.x = lectura.x*L3GD20_SENSITIVITY_500DPS;
	lectura.y = lectura.y*L3GD20_SENSITIVITY_500DPS;
	lectura.z = lectura.z*L3GD20_SENSITIVITY_500DPS;
	return lectura;
}


int main(void){
    clock_setup();
    console_setup(115200);

    spi_setup();
    input_setup();
    adc_setup();
    sdram_init();
    lcd_spi_init();

    msleep(2000);
	gfx_init(lcd_draw_pixel, 240, 320);


    while (1){
        // Mostrando información en pantalla
		gfx_fillScreen(LCD_WHITE);
		gfx_setTextColor(LCD_BLACK, LCD_WHITE);
		gfx_setTextSize(3);			
		gfx_setCursor(23, 30);
		gfx_puts(" Sismografo UCR ");		

		// Informacion de los ejes

        gfx_fillScreen(LCD_BLACK);
        gfx_setCursor(20, 30);
        gfx_puts("DATOS ");

		gfx_setCursor(20, 60);
        gfx_setTextSize(3);
		gfx_puts("Eje X");
		gfx_puts(lectura.x);
		
		gfx_setCursor(20, 100);
        gfx_setTextSize(3);
		gfx_puts("Eje Y");
		gfx_puts(lectura.y);

		gfx_setCursor(20, 140);
        gfx_setTextSize(3);
		gfx_puts("Eje Z");
		gfx_puts(lectura.z);


		// Informacion de la bateria
		gfx_setCursor(5, 200);
		gfx_puts("Bateria: ");
		gfx_setCursor(5, 240);
		gfx_puts(bat);
		gfx_puts(" V");

		// Informacion de transmisión
		gfx_setCursor(3, 270);
		gfx_puts("Trasmitiendo: ");

		if (transmision_enable){
			gfx_setCursor(205, 270);
			gfx_puts("Si");
		}
		else{
			gfx_setCursor(205, 270);
			gfx_puts("No");
		}
		lcd_show_frame();
		
		
		//Enviar datos
		lectura = read_xyz();
		gpio_set(GPIOC, GPIO1);

		// Se lee el puerto PA3 y se calcula el nivel de la tensión de la batería
		bateria_V = (read_adc_naiive(2)*9)/4095;
		
		// Se envia informacion solo si la transmision esta habilitada
		if (transmision_enable)
		{
			gpio_toggle(GPIOG, GPIO13); // Blink en el LED de transmisión

			console_puts(X_str);
			console_puts("\t");
			console_puts(Y_str);
			console_puts("\t");
			console_puts(Z_str);
			console_puts("\t");
			console_puts(bateria_V);
			console_puts("\n");
		}
		else{
			gpio_clear(GPIOG, GPIO13); // LED de transmisión se apaga
		}

		// Led de precaución por el nivel de la batería,
		// mayor a 7V se paga, sino hace blinking
		if (bateria_V<7)
		{
			gpio_toggle(GPIOG, GPIO14); // Blink en el LED de batería
		}

		else gpio_clear(GPIOG, GPIO14); //  LED de batería se apaga
		
		if (gpio_get(GPIOA, GPIO0)) {
			transmision_enable = ~transmision_enable;
			gpio_clear(GPIOG, GPIO13); //SE APAGA EL LED DE LA TRANSMISION
				
		}

		int i;
		for (i = 0; i < 80000; i++)    /* Wait a bit. */
			__asm__("nop");
		
	}
	return 0;
}