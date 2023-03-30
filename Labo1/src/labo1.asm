;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"labo1.c"
	list	p=12f683
	radix dec
	include "p12f683.inc"
;--------------------------------------------------------
; config word(s)
;--------------------------------------------------------
	__config 0x3fd7
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	__moduint
	extern	__divuint
	extern	__mulint
	extern	_printf
	extern	_TRISIO
	extern	_GPIO
	extern	_GPIObits
	extern	__sdcc_gsinit_startup
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_main
	global	_contabingo
	global	_contador
	global	_isInside
	global	_bingo
	global	_get_rand
	global	_check_array
	global	_addNumber
	global	_led_display
	global	_delay

	global PSAVE
	global SSAVE
	global WSAVE
	global STK12
	global STK11
	global STK10
	global STK09
	global STK08
	global STK07
	global STK06
	global STK05
	global STK04
	global STK03
	global STK02
	global STK01
	global STK00

sharebank udata_ovr 0x0070
PSAVE	res 1
SSAVE	res 1
WSAVE	res 1
STK12	res 1
STK11	res 1
STK10	res 1
STK09	res 1
STK08	res 1
STK07	res 1
STK06	res 1
STK05	res 1
STK04	res 1
STK03	res 1
STK02	res 1
STK01	res 1
STK00	res 1

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
UD_labo1_0	udata
_bingo	res	200

UD_labo1_1	udata
_contador	res	2

;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_labo1_0	udata
r0x10F1	res	1
r0x10F0	res	1
r0x10F3	res	1
r0x10F2	res	1
r0x10F5	res	1
r0x10F4	res	1
r0x10EB	res	1
r0x10EA	res	1
r0x10ED	res	1
r0x10EC	res	1
r0x10EF	res	1
r0x10EE	res	1
r0x10E1	res	1
r0x10E0	res	1
r0x10E2	res	1
r0x10E3	res	1
r0x10E4	res	1
r0x10E5	res	1
r0x10E6	res	1
r0x10E7	res	1
r0x10DD	res	1
r0x10DC	res	1
r0x10DF	res	1
r0x10DE	res	1
r0x10D9	res	1
r0x10D8	res	1
r0x10DA	res	1
r0x10D1	res	1
r0x10D0	res	1
r0x10D2	res	1
r0x10D3	res	1
r0x10D4	res	1
r0x10D5	res	1
r0x10D6	res	1
r0x10D7	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------

IDD_labo1_0	idata
_isInside
	db	0x00, 0x00	;  0


IDD_labo1_1	idata
_contabingo
	db	0x00, 0x00	; 0


IDD_labo1_2	idata
_get_rand_rand_65536_56
	db	0xe7, 0x03	; 999


IDC_labo1_3	code
___str_0
	retlw 0x25 ; '%'
	retlw 0x64 ; 'd'
	retlw 0x00 ; '.'
;--------------------------------------------------------
; initialized absolute data
;--------------------------------------------------------
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;	udata_ovr
;--------------------------------------------------------
; reset vector 
;--------------------------------------------------------
STARTUP	code 0x0000
	nop
	pagesel __sdcc_gsinit_startup
	goto	__sdcc_gsinit_startup
;--------------------------------------------------------
; code
;--------------------------------------------------------
code_labo1	code
;***
;  pBlock Stats: dbName = M
;***
;has an exit
;functions called:
;   _get_rand
;   _get_rand
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   __mulint
;   _printf
;   _check_array
;   _addNumber
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _get_rand
;   _get_rand
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   _led_display
;   _delay
;   __mulint
;   _printf
;   _check_array
;   _addNumber
;   _led_display
;   _delay
;   _led_display
;   _delay
;12 compiler assigned registers:
;   STK02
;   STK01
;   STK00
;   r0x10F0
;   r0x10F1
;   r0x10F2
;   r0x10F3
;   r0x10F4
;   r0x10F5
;   r0x10F6
;   r0x10F7
;   r0x10F8
;; Starting pCode block
S_labo1__main	code
_main:
; 2 exit points
;	.line	23; "labo1.c"	TRISIO = 0b00001000; // Poner todos los pines como salidas, GP3 como entrada por default
	MOVLW	0x08
	BANKSEL	_TRISIO
	MOVWF	_TRISIO
;	.line	24; "labo1.c"	GPIO = 0x00; //Poner pines en bajo
	BANKSEL	_GPIO
	CLRF	_GPIO
_00112_DS_:
;	.line	34; "labo1.c"	isInside = 0;
	BANKSEL	_isInside
	CLRF	_isInside
	CLRF	(_isInside + 1)
;	.line	36; "labo1.c"	numero1 = get_rand(0,9);
	MOVLW	0x09
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x00
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_get_rand
	CALL	_get_rand
	PAGESEL	$
	BANKSEL	r0x10F0
	MOVWF	r0x10F0
	MOVF	STK00,W
	MOVWF	r0x10F1
;	.line	37; "labo1.c"	numero2 = get_rand(0,9);
	MOVLW	0x09
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x00
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_get_rand
	CALL	_get_rand
	PAGESEL	$
	BANKSEL	r0x10F2
	MOVWF	r0x10F2
	MOVF	STK00,W
	MOVWF	r0x10F3
;	.line	41; "labo1.c"	led_display(numero1, 0);
	MOVLW	0x00
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVF	r0x10F1,W
	MOVWF	STK00
	MOVF	r0x10F0,W
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	42; "labo1.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	43; "labo1.c"	led_display(numero2, 1);
	MOVLW	0x01
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	BANKSEL	r0x10F3
	MOVF	r0x10F3,W
	MOVWF	STK00
	MOVF	r0x10F2,W
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	44; "labo1.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	46; "labo1.c"	contador = contador + 1;
	BANKSEL	_contador
	INCF	_contador,F
	BTFSC	STATUS,2
	INCF	(_contador + 1),F
;	.line	51; "labo1.c"	if (contador == 16)
	MOVF	_contador,W
	XORLW	0x10
	BTFSS	STATUS,2
	GOTO	_00106_DS_
	MOVF	(_contador + 1),W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00106_DS_
;	.line	53; "labo1.c"	led_display(9, 0);
	MOVLW	0x00
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x09
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	54; "labo1.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	55; "labo1.c"	led_display(9, 1);
	MOVLW	0x01
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x09
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	56; "labo1.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	57; "labo1.c"	led_display(9, 0);
	MOVLW	0x00
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x09
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	58; "labo1.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	59; "labo1.c"	led_display(9, 1);
	MOVLW	0x01
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x09
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	60; "labo1.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	61; "labo1.c"	led_display(9, 0);
	MOVLW	0x00
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x09
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	62; "labo1.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	63; "labo1.c"	led_display(9, 1);
	MOVLW	0x01
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x09
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	64; "labo1.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	65; "labo1.c"	led_display(9, 0);
	MOVLW	0x00
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x09
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	66; "labo1.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	67; "labo1.c"	led_display(9, 1);
	MOVLW	0x01
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x09
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	68; "labo1.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	71; "labo1.c"	contador = 0;
	BANKSEL	_contador
	CLRF	_contador
	CLRF	(_contador + 1)
_00106_DS_:
;	.line	74; "labo1.c"	if(GP3)  // Cuando el botón está presionado (configuración pull down)
	BANKSEL	_GPIObits
	BTFSS	_GPIObits,3
	GOTO	_00112_DS_
;	.line	76; "labo1.c"	numero = numero1*10 + numero2;
	BANKSEL	r0x10F1
	MOVF	r0x10F1,W
	MOVWF	STK02
	MOVF	r0x10F0,W
	MOVWF	STK01
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	__mulint
	CALL	__mulint
	PAGESEL	$
	BANKSEL	r0x10F4
	MOVWF	r0x10F4
	MOVF	STK00,W
	MOVWF	r0x10F5
	MOVF	r0x10F3,W
	ADDWF	r0x10F5,F
	MOVF	r0x10F2,W
	BTFSC	STATUS,0
	INCFSZ	r0x10F2,W
	ADDWF	r0x10F4,F
;	.line	77; "labo1.c"	printf("%d", numero);
	MOVLW	high (___str_0 + 0)
;;1	MOVWF	r0x10F6
	MOVLW	(___str_0 + 0)
;;1	MOVWF	r0x10F7
	MOVLW	0x80
;;1	MOVWF	r0x10F8
	PAGESEL	_printf
	CALL	_printf
	PAGESEL	$
;	.line	78; "labo1.c"	check_array(numero);
	BANKSEL	r0x10F5
	MOVF	r0x10F5,W
	MOVWF	STK00
	MOVF	r0x10F4,W
	PAGESEL	_check_array
	CALL	_check_array
	PAGESEL	$
;	.line	79; "labo1.c"	if(!isInside){
	BANKSEL	_isInside
	MOVF	(_isInside + 1),W
	IORWF	_isInside,W
	BTFSS	STATUS,2
	GOTO	_00112_DS_
;	.line	80; "labo1.c"	addNumber(numero);
	BANKSEL	r0x10F5
	MOVF	r0x10F5,W
	MOVWF	STK00
	MOVF	r0x10F4,W
	PAGESEL	_addNumber
	CALL	_addNumber
	PAGESEL	$
;	.line	81; "labo1.c"	led_display(numero1, 0);
	MOVLW	0x00
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	BANKSEL	r0x10F1
	MOVF	r0x10F1,W
	MOVWF	STK00
	MOVF	r0x10F0,W
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	82; "labo1.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	83; "labo1.c"	led_display(numero2, 1);
	MOVLW	0x01
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	BANKSEL	r0x10F3
	MOVF	r0x10F3,W
	MOVWF	STK00
	MOVF	r0x10F2,W
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	84; "labo1.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
	GOTO	_00112_DS_
;	.line	88; "labo1.c"	}
	RETURN	
; exit point of _main

;***
;  pBlock Stats: dbName = C
;***
;has an exit
;9 compiler assigned registers:
;   r0x10D0
;   STK00
;   r0x10D1
;   r0x10D2
;   r0x10D3
;   r0x10D4
;   r0x10D5
;   r0x10D6
;   r0x10D7
;; Starting pCode block
S_labo1__delay	code
_delay:
; 2 exit points
;	.line	163; "labo1.c"	void delay(unsigned int tiempo)
	BANKSEL	r0x10D0
	MOVWF	r0x10D0
	MOVF	STK00,W
	MOVWF	r0x10D1
;	.line	168; "labo1.c"	for(i=0;i<tiempo;i++)
	CLRF	r0x10D2
	CLRF	r0x10D3
_00219_DS_:
	BANKSEL	r0x10D0
	MOVF	r0x10D0,W
	SUBWF	r0x10D3,W
	BTFSS	STATUS,2
	GOTO	_00240_DS_
	MOVF	r0x10D1,W
	SUBWF	r0x10D2,W
_00240_DS_:
	BTFSC	STATUS,0
	GOTO	_00221_DS_
;;genSkipc:3307: created from rifx:0x7ffc9b184360
;	.line	169; "labo1.c"	for(j=0;j<1275;j++);
	MOVLW	0xfb
	BANKSEL	r0x10D4
	MOVWF	r0x10D4
	MOVLW	0x04
	MOVWF	r0x10D5
_00217_DS_:
	MOVLW	0xff
	BANKSEL	r0x10D4
	ADDWF	r0x10D4,W
	MOVWF	r0x10D6
	MOVLW	0xff
	MOVWF	r0x10D7
	MOVF	r0x10D5,W
	BTFSC	STATUS,0
	INCFSZ	r0x10D5,W
	ADDWF	r0x10D7,F
	MOVF	r0x10D6,W
	MOVWF	r0x10D4
	MOVF	r0x10D7,W
	MOVWF	r0x10D5
	MOVF	r0x10D7,W
	IORWF	r0x10D6,W
	BTFSS	STATUS,2
	GOTO	_00217_DS_
;	.line	168; "labo1.c"	for(i=0;i<tiempo;i++)
	INCF	r0x10D2,F
	BTFSC	STATUS,2
	INCF	r0x10D3,F
	GOTO	_00219_DS_
_00221_DS_:
;	.line	170; "labo1.c"	}
	RETURN	
; exit point of _delay

;***
;  pBlock Stats: dbName = C
;***
;has an exit
;7 compiler assigned registers:
;   r0x10D8
;   STK00
;   r0x10D9
;   STK01
;   r0x10DA
;   STK02
;   r0x10DB
;; Starting pCode block
S_labo1__led_display	code
_led_display:
; 2 exit points
;	.line	113; "labo1.c"	void led_display(int valor, int display)
	BANKSEL	r0x10D8
	MOVWF	r0x10D8
	MOVF	STK00,W
	MOVWF	r0x10D9
	MOVF	STK01,W
	MOVWF	r0x10DA
	MOVF	STK02,W
;;1	MOVWF	r0x10DB
;	.line	115; "labo1.c"	if (display == 0)
	IORWF	r0x10DA,W
	BTFSS	STATUS,2
	GOTO	_00206_DS_
;	.line	117; "labo1.c"	if (valor == 0) GPIO = 0b00000000;
	MOVF	r0x10D8,W
	IORWF	r0x10D9,W
	BTFSS	STATUS,2
	GOTO	_00176_DS_
	BANKSEL	_GPIO
	CLRF	_GPIO
	GOTO	_00208_DS_
_00176_DS_:
;	.line	119; "labo1.c"	else if (valor == 1) GPIO = 0b00000001; 
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x01
	BTFSS	STATUS,2
	GOTO	_00173_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00173_DS_
	MOVLW	0x01
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00173_DS_:
;	.line	121; "labo1.c"	else if (valor == 2) GPIO = 0b00000010; 
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x02
	BTFSS	STATUS,2
	GOTO	_00170_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00170_DS_
	MOVLW	0x02
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00170_DS_:
;	.line	123; "labo1.c"	else if (valor == 3) GPIO = 0b00000011;
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x03
	BTFSS	STATUS,2
	GOTO	_00167_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00167_DS_
	MOVLW	0x03
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00167_DS_:
;	.line	125; "labo1.c"	else if (valor == 4) GPIO = 0b00000100;
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x04
	BTFSS	STATUS,2
	GOTO	_00164_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00164_DS_
	MOVLW	0x04
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00164_DS_:
;	.line	127; "labo1.c"	else if (valor == 5) GPIO = 0b00000101;
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x05
	BTFSS	STATUS,2
	GOTO	_00161_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00161_DS_
	MOVLW	0x05
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00161_DS_:
;	.line	129; "labo1.c"	else if (valor == 6) GPIO = 0b00000110;
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x06
	BTFSS	STATUS,2
	GOTO	_00158_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00158_DS_
	MOVLW	0x06
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00158_DS_:
;	.line	131; "labo1.c"	else if (valor == 7) GPIO = 0b00000111;
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x07
	BTFSS	STATUS,2
	GOTO	_00155_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00155_DS_
	MOVLW	0x07
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00155_DS_:
;	.line	133; "labo1.c"	else if (valor == 8) GPIO = 0b00010000;
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x08
	BTFSS	STATUS,2
	GOTO	_00152_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00152_DS_
	MOVLW	0x10
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00152_DS_:
;	.line	135; "labo1.c"	else GPIO = 0b00010001;
	MOVLW	0x11
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00206_DS_:
;	.line	140; "labo1.c"	if (valor == 0) GPIO = 0b00100000;
	BANKSEL	r0x10D8
	MOVF	r0x10D8,W
	IORWF	r0x10D9,W
	BTFSS	STATUS,2
	GOTO	_00203_DS_
	MOVLW	0x20
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00203_DS_:
;	.line	142; "labo1.c"	else if (valor == 1) GPIO = 0b00100001; 
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x01
	BTFSS	STATUS,2
	GOTO	_00200_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00200_DS_
	MOVLW	0x21
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00200_DS_:
;	.line	144; "labo1.c"	else if (valor == 2) GPIO = 0b00100010; 
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x02
	BTFSS	STATUS,2
	GOTO	_00197_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00197_DS_
	MOVLW	0x22
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00197_DS_:
;	.line	146; "labo1.c"	else if (valor == 3) GPIO = 0b00100011;
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x03
	BTFSS	STATUS,2
	GOTO	_00194_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00194_DS_
	MOVLW	0x23
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00194_DS_:
;	.line	148; "labo1.c"	else if (valor == 4) GPIO = 0b00100100;
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x04
	BTFSS	STATUS,2
	GOTO	_00191_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00191_DS_
	MOVLW	0x24
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00191_DS_:
;	.line	150; "labo1.c"	else if (valor == 5) GPIO = 0b00100101;
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x05
	BTFSS	STATUS,2
	GOTO	_00188_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00188_DS_
	MOVLW	0x25
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00188_DS_:
;	.line	152; "labo1.c"	else if (valor == 6) GPIO = 0b00100110;
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x06
	BTFSS	STATUS,2
	GOTO	_00185_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00185_DS_
	MOVLW	0x26
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00185_DS_:
;	.line	154; "labo1.c"	else if (valor == 7) GPIO = 0b00100111;
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x07
	BTFSS	STATUS,2
	GOTO	_00182_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00182_DS_
	MOVLW	0x27
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00182_DS_:
;	.line	156; "labo1.c"	else if (valor == 8) GPIO = 0b00110000;
	BANKSEL	r0x10D9
	MOVF	r0x10D9,W
	XORLW	0x08
	BTFSS	STATUS,2
	GOTO	_00179_DS_
	MOVF	r0x10D8,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00179_DS_
	MOVLW	0x30
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00208_DS_
_00179_DS_:
;	.line	158; "labo1.c"	else GPIO = 0b00110001;
	MOVLW	0x31
	BANKSEL	_GPIO
	MOVWF	_GPIO
_00208_DS_:
;	.line	160; "labo1.c"	}
	RETURN	
; exit point of _led_display

;***
;  pBlock Stats: dbName = C
;***
;has an exit
;functions called:
;   __mulint
;   __mulint
;7 compiler assigned registers:
;   r0x10DC
;   STK00
;   r0x10DD
;   STK02
;   STK01
;   r0x10DE
;   r0x10DF
;; Starting pCode block
S_labo1__addNumber	code
_addNumber:
; 2 exit points
;	.line	107; "labo1.c"	void addNumber(unsigned int num){
	BANKSEL	r0x10DC
	MOVWF	r0x10DC
	MOVF	STK00,W
	MOVWF	r0x10DD
;	.line	108; "labo1.c"	bingo[contabingo] = num;
	BANKSEL	_contabingo
	MOVF	_contabingo,W
	MOVWF	STK02
	MOVF	(_contabingo + 1),W
	MOVWF	STK01
	MOVLW	0x02
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	__mulint
	CALL	__mulint
	PAGESEL	$
	BANKSEL	r0x10DE
	MOVWF	r0x10DE
	MOVF	STK00,W
	MOVWF	r0x10DF
	ADDLW	(_bingo + 0)
	MOVWF	r0x10DF
	MOVF	r0x10DE,W
	BTFSC	STATUS,0
	INCFSZ	r0x10DE,W
	ADDLW	high (_bingo + 0)
	MOVWF	r0x10DE
	MOVF	r0x10DF,W
	BANKSEL	FSR
	MOVWF	FSR
	BCF	STATUS,7
	BANKSEL	r0x10DE
	BTFSC	r0x10DE,0
	BSF	STATUS,7
	MOVF	r0x10DD,W
	BANKSEL	INDF
	MOVWF	INDF
	INCF	FSR,F
	BANKSEL	r0x10DC
	MOVF	r0x10DC,W
	BANKSEL	INDF
	MOVWF	INDF
;	.line	109; "labo1.c"	contabingo++;
	BANKSEL	_contabingo
	INCF	_contabingo,F
	BTFSC	STATUS,2
	INCF	(_contabingo + 1),F
;	.line	110; "labo1.c"	}
	RETURN	
; exit point of _addNumber

;***
;  pBlock Stats: dbName = C
;***
;has an exit
;11 compiler assigned registers:
;   r0x10E0
;   STK00
;   r0x10E1
;   r0x10E2
;   r0x10E3
;   r0x10E4
;   r0x10E5
;   r0x10E6
;   r0x10E7
;   r0x10E8
;   r0x10E9
;; Starting pCode block
S_labo1__check_array	code
_check_array:
; 2 exit points
;	.line	101; "labo1.c"	void check_array(unsigned int num){
	BANKSEL	r0x10E0
	MOVWF	r0x10E0
	MOVF	STK00,W
	MOVWF	r0x10E1
;	.line	102; "labo1.c"	for(int i = 0; i < 100; i++){
	CLRF	r0x10E2
	CLRF	r0x10E3
	CLRF	r0x10E4
	CLRF	r0x10E5
;;signed compare: left < lit(0x64=100), size=2, mask=ffff
_00125_DS_:
	BANKSEL	r0x10E3
	MOVF	r0x10E3,W
	ADDLW	0x80
	ADDLW	0x80
	BTFSS	STATUS,2
	GOTO	_00142_DS_
	MOVLW	0x64
	SUBWF	r0x10E2,W
_00142_DS_:
	BTFSC	STATUS,0
	GOTO	_00127_DS_
;;genSkipc:3307: created from rifx:0x7ffc9b184360
;	.line	103; "labo1.c"	if(bingo[i] == num) isInside = 1;
	BANKSEL	r0x10E4
	MOVF	r0x10E4,W
	ADDLW	(_bingo + 0)
	MOVWF	r0x10E6
	MOVLW	high (_bingo + 0)
	MOVWF	r0x10E7
	MOVF	r0x10E5,W
	BTFSC	STATUS,0
	INCFSZ	r0x10E5,W
	ADDWF	r0x10E7,F
	MOVF	r0x10E6,W
	BANKSEL	FSR
	MOVWF	FSR
	BCF	STATUS,7
	BANKSEL	r0x10E7
	BTFSC	r0x10E7,0
	BSF	STATUS,7
	BANKSEL	INDF
	MOVF	INDF,W
	BANKSEL	r0x10E6
	MOVWF	r0x10E6
;;1	MOVWF	r0x10E8
	BANKSEL	FSR
	INCF	FSR,F
	MOVF	INDF,W
	BANKSEL	r0x10E7
	MOVWF	r0x10E7
;;1	MOVWF	r0x10E9
;;99	MOVF	r0x10E8,W
;;100	MOVF	r0x10E9,W
	MOVF	r0x10E1,W
	XORWF	r0x10E6,W
	BTFSS	STATUS,2
	GOTO	_00126_DS_
	MOVF	r0x10E0,W
	XORWF	r0x10E7,W
	BTFSS	STATUS,2
	GOTO	_00126_DS_
	MOVLW	0x01
	BANKSEL	_isInside
	MOVWF	_isInside
	CLRF	(_isInside + 1)
_00126_DS_:
;	.line	102; "labo1.c"	for(int i = 0; i < 100; i++){
	MOVLW	0x02
	BANKSEL	r0x10E4
	ADDWF	r0x10E4,F
	BTFSC	STATUS,0
	INCF	r0x10E5,F
	INCF	r0x10E2,F
	BTFSC	STATUS,2
	INCF	r0x10E3,F
	GOTO	_00125_DS_
_00127_DS_:
;	.line	105; "labo1.c"	}
	RETURN	
; exit point of _check_array

;***
;  pBlock Stats: dbName = C
;***
;has an exit
;functions called:
;   __mulint
;   __divuint
;   __moduint
;   __moduint
;   __mulint
;   __divuint
;   __moduint
;   __moduint
;9 compiler assigned registers:
;   r0x10EA
;   STK00
;   r0x10EB
;   STK01
;   r0x10EC
;   STK02
;   r0x10ED
;   r0x10EE
;   r0x10EF
;; Starting pCode block
S_labo1__get_rand	code
_get_rand:
; 2 exit points
;	.line	91; "labo1.c"	unsigned int get_rand(unsigned int min, unsigned int max)
	BANKSEL	r0x10EA
	MOVWF	r0x10EA
	MOVF	STK00,W
	MOVWF	r0x10EB
	MOVF	STK01,W
	MOVWF	r0x10EC
	MOVF	STK02,W
	MOVWF	r0x10ED
;	.line	95; "labo1.c"	rand += ((rand * rand) /100) % 10000;
	BANKSEL	_get_rand_rand_65536_56
	MOVF	_get_rand_rand_65536_56,W
	MOVWF	STK02
	MOVF	(_get_rand_rand_65536_56 + 1),W
	MOVWF	STK01
	MOVF	_get_rand_rand_65536_56,W
	MOVWF	STK00
	MOVF	(_get_rand_rand_65536_56 + 1),W
	PAGESEL	__mulint
	CALL	__mulint
	PAGESEL	$
	BANKSEL	r0x10EE
	MOVWF	r0x10EE
	MOVF	STK00,W
	MOVWF	r0x10EF
	MOVLW	0x64
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVF	r0x10EF,W
	MOVWF	STK00
	MOVF	r0x10EE,W
	PAGESEL	__divuint
	CALL	__divuint
	PAGESEL	$
	BANKSEL	r0x10EE
	MOVWF	r0x10EE
	MOVF	STK00,W
	MOVWF	r0x10EF
	MOVLW	0x10
	MOVWF	STK02
	MOVLW	0x27
	MOVWF	STK01
	MOVF	r0x10EF,W
	MOVWF	STK00
	MOVF	r0x10EE,W
	PAGESEL	__moduint
	CALL	__moduint
	PAGESEL	$
	BANKSEL	r0x10EE
	MOVWF	r0x10EE
	MOVF	STK00,W
	MOVWF	r0x10EF
	BANKSEL	_get_rand_rand_65536_56
	ADDWF	_get_rand_rand_65536_56,F
	BANKSEL	r0x10EE
	MOVF	r0x10EE,W
	BTFSC	STATUS,0
	INCF	r0x10EE,W
	BTFSC	STATUS,2
	GOTO	_00001_DS_
	BANKSEL	_get_rand_rand_65536_56
	ADDWF	(_get_rand_rand_65536_56 + 1),F
_00001_DS_:
;	.line	97; "labo1.c"	return rand % (max+1-min)+min;
	BANKSEL	r0x10ED
	INCF	r0x10ED,F
	BTFSC	STATUS,2
	INCF	r0x10EC,F
	MOVF	r0x10EB,W
	SUBWF	r0x10ED,F
	MOVF	r0x10EA,W
	BTFSS	STATUS,0
	INCFSZ	r0x10EA,W
	SUBWF	r0x10EC,F
	MOVF	r0x10ED,W
	MOVWF	STK02
	MOVF	r0x10EC,W
	MOVWF	STK01
	BANKSEL	_get_rand_rand_65536_56
	MOVF	_get_rand_rand_65536_56,W
	MOVWF	STK00
	MOVF	(_get_rand_rand_65536_56 + 1),W
	PAGESEL	__moduint
	CALL	__moduint
	PAGESEL	$
	BANKSEL	r0x10EC
	MOVWF	r0x10EC
	MOVF	STK00,W
	MOVWF	r0x10ED
	MOVF	r0x10EB,W
	ADDWF	r0x10ED,W
	MOVWF	r0x10EB
	MOVF	r0x10EC,W
	BTFSC	STATUS,0
	INCFSZ	r0x10EC,W
	ADDWF	r0x10EA,F
	MOVF	r0x10EB,W
	MOVWF	STK00
	MOVF	r0x10EA,W
;	.line	99; "labo1.c"	}
	RETURN	
; exit point of _get_rand


;	code size estimation:
;	  632+  159 =   791 instructions ( 1900 byte)

	end
