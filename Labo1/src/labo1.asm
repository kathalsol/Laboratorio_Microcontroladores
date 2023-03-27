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
; external declarations
;--------------------------------------------------------
	extern	__moduint
	extern	__divuint
	extern	__mulint
	extern	_TRISIO
	extern	_GPIO
	extern	_GPIObits
	extern	__sdcc_gsinit_startup
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_main
	global	_get_rand
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
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_labo1_0	udata
r0x1015	res	1
r0x1014	res	1
r0x1017	res	1
r0x1016	res	1
r0x100F	res	1
r0x100E	res	1
r0x1011	res	1
r0x1010	res	1
r0x1013	res	1
r0x1012	res	1
r0x100B	res	1
r0x100A	res	1
r0x100D	res	1
r0x100C	res	1
r0x1003	res	1
r0x1002	res	1
r0x1004	res	1
r0x1005	res	1
r0x1006	res	1
r0x1007	res	1
r0x1008	res	1
r0x1009	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------

IDD_labo1_0	idata
_get_rand_rand_65536_11
	db	0xe7, 0x03	; 999

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
;7 compiler assigned registers:
;   STK02
;   STK01
;   STK00
;   r0x1014
;   r0x1015
;   r0x1016
;   r0x1017
;; Starting pCode block
S_labo1__main	code
_main:
; 2 exit points
;	.line	9; "labo1.c"	TRISIO = 0b00000000; // Poner todos los pines como salidas
	BANKSEL	_TRISIO
	CLRF	_TRISIO
;	.line	10; "labo1.c"	GPIO = 0x00; //Poner pines en bajo
	BANKSEL	_GPIO
	CLRF	_GPIO
_00111_DS_:
;	.line	20; "labo1.c"	numero1 = get_rand(0,9);
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
	BANKSEL	r0x1014
	MOVWF	r0x1014
	MOVF	STK00,W
	MOVWF	r0x1015
;	.line	21; "labo1.c"	numero2 = get_rand(0,9);
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
	BANKSEL	r0x1016
	MOVWF	r0x1016
	MOVF	STK00,W
	MOVWF	r0x1017
;	.line	23; "labo1.c"	if(GP3)
	BANKSEL	_GPIObits
	BTFSS	_GPIObits,3
	GOTO	_00109_DS_
_00105_DS_:
;	.line	25; "labo1.c"	while(GP3)
	BANKSEL	_GPIObits
	BTFSS	_GPIObits,3
	GOTO	_00109_DS_
;	.line	27; "labo1.c"	led_display(numero1, 0);
	MOVLW	0x00
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	BANKSEL	r0x1015
	MOVF	r0x1015,W
	MOVWF	STK00
	MOVF	r0x1014,W
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	28; "labo1.c"	delay(time);
	MOVLW	0x05
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	29; "labo1.c"	led_display(numero2, 1);
	MOVLW	0x01
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	BANKSEL	r0x1017
	MOVF	r0x1017,W
	MOVWF	STK00
	MOVF	r0x1016,W
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	30; "labo1.c"	delay(time);
	MOVLW	0x05
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
	GOTO	_00105_DS_
_00109_DS_:
;	.line	35; "labo1.c"	led_display(numero1, 0);
	MOVLW	0x00
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	BANKSEL	r0x1015
	MOVF	r0x1015,W
	MOVWF	STK00
	MOVF	r0x1014,W
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	36; "labo1.c"	delay(time);
	MOVLW	0x05
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	37; "labo1.c"	led_display(numero2, 1);
	MOVLW	0x01
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	BANKSEL	r0x1017
	MOVF	r0x1017,W
	MOVWF	STK00
	MOVF	r0x1016,W
	PAGESEL	_led_display
	CALL	_led_display
	PAGESEL	$
;	.line	38; "labo1.c"	delay(time);
	MOVLW	0x05
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
	GOTO	_00111_DS_
;	.line	41; "labo1.c"	}
	RETURN	
; exit point of _main

;***
;  pBlock Stats: dbName = C
;***
;has an exit
;9 compiler assigned registers:
;   r0x1002
;   STK00
;   r0x1003
;   r0x1004
;   r0x1005
;   r0x1006
;   r0x1007
;   r0x1008
;   r0x1009
;; Starting pCode block
S_labo1__delay	code
_delay:
; 2 exit points
;	.line	104; "labo1.c"	void delay(unsigned int tiempo)
	BANKSEL	r0x1002
	MOVWF	r0x1002
	MOVF	STK00,W
	MOVWF	r0x1003
;	.line	109; "labo1.c"	for(i=0;i<tiempo;i++)
	CLRF	r0x1004
	CLRF	r0x1005
_00190_DS_:
	BANKSEL	r0x1002
	MOVF	r0x1002,W
	SUBWF	r0x1005,W
	BTFSS	STATUS,2
	GOTO	_00211_DS_
	MOVF	r0x1003,W
	SUBWF	r0x1004,W
_00211_DS_:
	BTFSC	STATUS,0
	GOTO	_00192_DS_
;;genSkipc:3307: created from rifx:0x7ffc18614e20
;	.line	110; "labo1.c"	for(j=0;j<1275;j++);
	MOVLW	0xfb
	BANKSEL	r0x1006
	MOVWF	r0x1006
	MOVLW	0x04
	MOVWF	r0x1007
_00188_DS_:
	MOVLW	0xff
	BANKSEL	r0x1006
	ADDWF	r0x1006,W
	MOVWF	r0x1008
	MOVLW	0xff
	MOVWF	r0x1009
	MOVF	r0x1007,W
	BTFSC	STATUS,0
	INCFSZ	r0x1007,W
	ADDWF	r0x1009,F
	MOVF	r0x1008,W
	MOVWF	r0x1006
	MOVF	r0x1009,W
	MOVWF	r0x1007
	MOVF	r0x1009,W
	IORWF	r0x1008,W
	BTFSS	STATUS,2
	GOTO	_00188_DS_
;	.line	109; "labo1.c"	for(i=0;i<tiempo;i++)
	INCF	r0x1004,F
	BTFSC	STATUS,2
	INCF	r0x1005,F
	GOTO	_00190_DS_
_00192_DS_:
;	.line	111; "labo1.c"	}
	RETURN	
; exit point of _delay

;***
;  pBlock Stats: dbName = C
;***
;has an exit
;7 compiler assigned registers:
;   r0x100A
;   STK00
;   r0x100B
;   STK01
;   r0x100C
;   STK02
;   r0x100D
;; Starting pCode block
S_labo1__led_display	code
_led_display:
; 2 exit points
;	.line	55; "labo1.c"	void led_display(int valor, int display)
	BANKSEL	r0x100A
	MOVWF	r0x100A
	MOVF	STK00,W
	MOVWF	r0x100B
	MOVF	STK01,W
	MOVWF	r0x100C
	MOVF	STK02,W
;	.line	57; "labo1.c"	if (display == 0)
	MOVWF	r0x100D
	IORWF	r0x100C,W
	BTFSS	STATUS,2
	GOTO	_00177_DS_
;	.line	59; "labo1.c"	if (valor == 0) GPIO = 0b00000000;
	MOVF	r0x100A,W
	IORWF	r0x100B,W
	BTFSS	STATUS,2
	GOTO	_00145_DS_
	BANKSEL	_GPIO
	CLRF	_GPIO
	GOTO	_00179_DS_
_00145_DS_:
;	.line	61; "labo1.c"	else if (valor == 1) GPIO = 0b00000001; 
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x01
	BTFSS	STATUS,2
	GOTO	_00142_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00142_DS_
	MOVLW	0x01
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00142_DS_:
;	.line	63; "labo1.c"	else if (valor == 2) GPIO = 0b00000010; 
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x02
	BTFSS	STATUS,2
	GOTO	_00139_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00139_DS_
	MOVLW	0x02
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00139_DS_:
;	.line	65; "labo1.c"	else if (valor == 3) GPIO = 0b00000011;
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x03
	BTFSS	STATUS,2
	GOTO	_00136_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00136_DS_
	MOVLW	0x03
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00136_DS_:
;	.line	67; "labo1.c"	else if (valor == 4) GPIO = 0b00000100;
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x04
	BTFSS	STATUS,2
	GOTO	_00133_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00133_DS_
	MOVLW	0x04
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00133_DS_:
;	.line	69; "labo1.c"	else if (valor == 5) GPIO = 0b00000101;
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x05
	BTFSS	STATUS,2
	GOTO	_00130_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00130_DS_
	MOVLW	0x05
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00130_DS_:
;	.line	71; "labo1.c"	else if (valor == 6) GPIO = 0b00000110;
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x06
	BTFSS	STATUS,2
	GOTO	_00127_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00127_DS_
	MOVLW	0x06
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00127_DS_:
;	.line	73; "labo1.c"	else if (valor == 7) GPIO = 0b00000111;
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x07
	BTFSS	STATUS,2
	GOTO	_00124_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00124_DS_
	MOVLW	0x07
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00124_DS_:
;	.line	75; "labo1.c"	else if (valor == 8) GPIO = 0b00010000;
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x08
	BTFSS	STATUS,2
	GOTO	_00121_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00121_DS_
	MOVLW	0x10
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00121_DS_:
;	.line	77; "labo1.c"	else GPIO = 0b00010001;
	MOVLW	0x11
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00177_DS_:
;	.line	80; "labo1.c"	else if (display == 1)
	BANKSEL	r0x100D
	MOVF	r0x100D,W
	XORLW	0x01
	BTFSS	STATUS,2
	GOTO	_00179_DS_
	MOVF	r0x100C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00179_DS_
;	.line	82; "labo1.c"	if (valor == 0) GPIO = 0b00100000;
	MOVF	r0x100A,W
	IORWF	r0x100B,W
	BTFSS	STATUS,2
	GOTO	_00172_DS_
	MOVLW	0x20
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00172_DS_:
;	.line	84; "labo1.c"	else if (valor == 1) GPIO = 0b00100001; 
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x01
	BTFSS	STATUS,2
	GOTO	_00169_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00169_DS_
	MOVLW	0x21
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00169_DS_:
;	.line	86; "labo1.c"	else if (valor == 2) GPIO = 0b00100010; 
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x02
	BTFSS	STATUS,2
	GOTO	_00166_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00166_DS_
	MOVLW	0x22
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00166_DS_:
;	.line	88; "labo1.c"	else if (valor == 3) GPIO = 0b00100011;
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x03
	BTFSS	STATUS,2
	GOTO	_00163_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00163_DS_
	MOVLW	0x23
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00163_DS_:
;	.line	90; "labo1.c"	else if (valor == 4) GPIO = 0b00100100;
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x04
	BTFSS	STATUS,2
	GOTO	_00160_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00160_DS_
	MOVLW	0x24
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00160_DS_:
;	.line	92; "labo1.c"	else if (valor == 5) GPIO = 0b00100101;
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x05
	BTFSS	STATUS,2
	GOTO	_00157_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00157_DS_
	MOVLW	0x25
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00157_DS_:
;	.line	94; "labo1.c"	else if (valor == 6) GPIO = 0b00100110;
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x06
	BTFSS	STATUS,2
	GOTO	_00154_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00154_DS_
	MOVLW	0x26
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00154_DS_:
;	.line	96; "labo1.c"	else if (valor == 7) GPIO = 0b00100111;
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x07
	BTFSS	STATUS,2
	GOTO	_00151_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00151_DS_
	MOVLW	0x27
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00151_DS_:
;	.line	98; "labo1.c"	else if (valor == 8) GPIO = 0b00110000;
	BANKSEL	r0x100B
	MOVF	r0x100B,W
	XORLW	0x08
	BTFSS	STATUS,2
	GOTO	_00148_DS_
	MOVF	r0x100A,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00148_DS_
	MOVLW	0x30
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00179_DS_
_00148_DS_:
;	.line	100; "labo1.c"	else GPIO = 0b00110001;
	MOVLW	0x31
	BANKSEL	_GPIO
	MOVWF	_GPIO
_00179_DS_:
;	.line	102; "labo1.c"	}
	RETURN	
; exit point of _led_display

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
;   r0x100E
;   STK00
;   r0x100F
;   STK01
;   r0x1010
;   STK02
;   r0x1011
;   r0x1012
;   r0x1013
;; Starting pCode block
S_labo1__get_rand	code
_get_rand:
; 2 exit points
;	.line	44; "labo1.c"	unsigned int get_rand(unsigned int min, unsigned int max)
	BANKSEL	r0x100E
	MOVWF	r0x100E
	MOVF	STK00,W
	MOVWF	r0x100F
	MOVF	STK01,W
	MOVWF	r0x1010
	MOVF	STK02,W
	MOVWF	r0x1011
;	.line	48; "labo1.c"	rand += ((rand * rand) /100) % 10000;
	BANKSEL	_get_rand_rand_65536_11
	MOVF	_get_rand_rand_65536_11,W
	MOVWF	STK02
	MOVF	(_get_rand_rand_65536_11 + 1),W
	MOVWF	STK01
	MOVF	_get_rand_rand_65536_11,W
	MOVWF	STK00
	MOVF	(_get_rand_rand_65536_11 + 1),W
	PAGESEL	__mulint
	CALL	__mulint
	PAGESEL	$
	BANKSEL	r0x1012
	MOVWF	r0x1012
	MOVF	STK00,W
	MOVWF	r0x1013
	MOVLW	0x64
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVF	r0x1013,W
	MOVWF	STK00
	MOVF	r0x1012,W
	PAGESEL	__divuint
	CALL	__divuint
	PAGESEL	$
	BANKSEL	r0x1012
	MOVWF	r0x1012
	MOVF	STK00,W
	MOVWF	r0x1013
	MOVLW	0x10
	MOVWF	STK02
	MOVLW	0x27
	MOVWF	STK01
	MOVF	r0x1013,W
	MOVWF	STK00
	MOVF	r0x1012,W
	PAGESEL	__moduint
	CALL	__moduint
	PAGESEL	$
	BANKSEL	r0x1012
	MOVWF	r0x1012
	MOVF	STK00,W
	MOVWF	r0x1013
	BANKSEL	_get_rand_rand_65536_11
	ADDWF	_get_rand_rand_65536_11,F
	BANKSEL	r0x1012
	MOVF	r0x1012,W
	BTFSC	STATUS,0
	INCF	r0x1012,W
	BTFSC	STATUS,2
	GOTO	_00001_DS_
	BANKSEL	_get_rand_rand_65536_11
	ADDWF	(_get_rand_rand_65536_11 + 1),F
_00001_DS_:
;	.line	50; "labo1.c"	return rand % (max+1-min)+min;
	BANKSEL	r0x1011
	INCF	r0x1011,F
	BTFSC	STATUS,2
	INCF	r0x1010,F
	MOVF	r0x100F,W
	SUBWF	r0x1011,F
	MOVF	r0x100E,W
	BTFSS	STATUS,0
	INCFSZ	r0x100E,W
	SUBWF	r0x1010,F
	MOVF	r0x1011,W
	MOVWF	STK02
	MOVF	r0x1010,W
	MOVWF	STK01
	BANKSEL	_get_rand_rand_65536_11
	MOVF	_get_rand_rand_65536_11,W
	MOVWF	STK00
	MOVF	(_get_rand_rand_65536_11 + 1),W
	PAGESEL	__moduint
	CALL	__moduint
	PAGESEL	$
	BANKSEL	r0x1010
	MOVWF	r0x1010
	MOVF	STK00,W
	MOVWF	r0x1011
	MOVF	r0x100F,W
	ADDWF	r0x1011,W
	MOVWF	r0x100F
	MOVF	r0x1010,W
	BTFSC	STATUS,0
	INCFSZ	r0x1010,W
	ADDWF	r0x100E,F
	MOVF	r0x100F,W
	MOVWF	STK00
	MOVF	r0x100E,W
;	.line	52; "labo1.c"	}
	RETURN	
; exit point of _get_rand


;	code size estimation:
;	  409+   91 =   500 instructions ( 1182 byte)

	end
