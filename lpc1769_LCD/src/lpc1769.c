/*
===============================================================================
 Name        : lpc1769.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "lpc1769.h"
#include "lcd.h"

// LCD
char lcd_BP = 0;	// valore logico BackPlane
char lcd_TX;		// valore logico TX
char lcd_1BC;		// valore logico 1BC
char lcd_DP1;		// valore logico DP1
char lcd_2E;		// valore logico 2E
char lcd_2D;		// valore logico 2D
char lcd_2C;		// valore logico 2C
char lcd_DP2;		// valore logico DP2
char lcd_3E;		// valore logico 3E
char lcd_3D;		// valore logico 3D
char lcd_3C;		// valore logico 3C
char lcd_DP3;		// valore logico DP3
char lcd_4E;		// valore logico 4E
char lcd_4D;		// valore logico 4D
char lcd_4C;		// valore logico 4C
char lcd_4B;		// valore logico 4B
char lcd_4A;		// valore logico 4A
char lcd_4F;		// valore logico 4F
char lcd_4G;		// valore logico 4G
char lcd_3B;		// valore logico 3B
char lcd_3A;		// valore logico 3A
char lcd_3F;		// valore logico 3F
char lcd_3G;		// valore logico 3G
char lcd_COL;		// valore logico COL
char lcd_2B;		// valore logico 2B
char lcd_2A;		// valore logico 2A
char lcd_2F;		// valore logico 2F
char lcd_2G;		// valore logico 2G
char lcd_LOBAT;		// valore logico LOBAT
char lcd_TY;		// valore logico TY


// Gestore di interrupt dal timer di sistema
void SysTick_Handler(void)
{
	//**********************************
	// funzione di prova per il conteggio
	// da eliminare
	static int time_counter=0;
	static int val_counter=0;
	int val;

	time_counter++;
	if(time_counter>1)
	{
		time_counter=0;

		val=val_counter;
		setDigit4(val%10);
		val/=10;
		setDigit3(val%10);
		val/=10;
		setDigit2(val%10);
		val/=10;
		setDigit1(val%10);

		val_counter++;
		if(val_counter>1999)
			val_counter=0;
	}
	//************************************


	// gestione valore BackPlane su P0.9
	lcd_BP = !lcd_BP;				// inversione del valore logico BackPlane
	FIO0MASK = ~(1<<9);				// imposta la maschera per modificare solo il bit 9 di P0
	FIO0PIN = lcd_BP<<9;			// aggiorna il valore di P0.9


	// gestione valore TX su P0.8
	FIO0MASK = ~(1<<8);				// imposta la maschera per modificare solo il bit 8 di P0
	if(lcd_TX)
		FIO0PIN = (!lcd_BP)<<8;		// aggiorna il valore di P0.8
	else
		FIO0PIN = lcd_BP<<8;		// aggiorna il valore di P0.8

	// gestione valore 1BC su P0.7
	FIO0MASK = ~(1<<7);				// imposta la maschera per modificare solo il bit 7 di P0
	if(lcd_1BC)
		FIO0PIN = (!lcd_BP)<<7;		// aggiorna il valore di P0.7
	else
		FIO0PIN = lcd_BP<<7;		// aggiorna il valore di P0.7

	// gestione valore DP1 su P0.6
	FIO0MASK = ~(1<<6);				// imposta la maschera per modificare solo il bit 6 di P0
	if(lcd_DP1)
		FIO0PIN = (!lcd_BP)<<6;		// aggiorna il valore di P0.6
	else
		FIO0PIN = lcd_BP<<6;		// aggiorna il valore di P0.6

	// gestione valore 2E su P0.0
	FIO0MASK = ~(1<<0);				// imposta la maschera per modificare solo il bit 0 di P0
	if(lcd_2E)
		FIO0PIN = (!lcd_BP)<<0;		// aggiorna il valore di P0.0
	else
		FIO0PIN = lcd_BP<<0;		// aggiorna il valore di P0.0

	// gestione valore 2D su P0.1
	FIO0MASK = ~(1<<1);				// imposta la maschera per modificare solo il bit 1 di P0
	if(lcd_2D)
		FIO0PIN = (!lcd_BP)<<1;		// aggiorna il valore di P0.1
	else
		FIO0PIN = lcd_BP<<1;		// aggiorna il valore di P0.1

	// gestione valore 2C su P0.18
	FIO0MASK = ~(1<<18);			// imposta la maschera per modificare solo il bit 18 di P0
	if(lcd_2C)
		FIO0PIN = (!lcd_BP)<<18;	// aggiorna il valore di P0.18
	else
		FIO0PIN = lcd_BP<<18;		// aggiorna il valore di P0.18

	// gestione valore DP2 su P0.17
	FIO0MASK = ~(1<<17);			// imposta la maschera per modificare solo il bit 17 di P0
	if(lcd_DP2)
		FIO0PIN = (!lcd_BP)<<17;	// aggiorna il valore di P0.17
	else
		FIO0PIN = lcd_BP<<17;		// aggiorna il valore di P0.17

	// gestione valore 3E su P0.15
	FIO0MASK = ~(1<<15);			// imposta la maschera per modificare solo il bit 15 di P0
	if(lcd_3E)
		FIO0PIN = (!lcd_BP)<<15;	// aggiorna il valore di P0.15
	else
		FIO0PIN = lcd_BP<<15;		// aggiorna il valore di P0.15

	// gestione valore 3D su P0.16
	FIO0MASK = ~(1<<16);			// imposta la maschera per modificare solo il bit 16 di P0
	if(lcd_3D)
		FIO0PIN = (!lcd_BP)<<16;	// aggiorna il valore di P0.16
	else
		FIO0PIN = lcd_BP<<16;		// aggiorna il valore di P0.16

	// gestione valore 3C su P0.23
	FIO0MASK = ~(1<<23);			// imposta la maschera per modificare solo il bit 23 di P0
	if(lcd_3C)
		FIO0PIN = (!lcd_BP)<<23;	// aggiorna il valore di P0.23
	else
		FIO0PIN = lcd_BP<<23;		// aggiorna il valore di P0.23

	// gestione valore DP3 su P0.24
	FIO0MASK = ~(1<<24);			// imposta la maschera per modificare solo il bit 24 di P0
	if(lcd_DP3)
		FIO0PIN = (!lcd_BP)<<24;	// aggiorna il valore di P0.24
	else
		FIO0PIN = lcd_BP<<24;		// aggiorna il valore di P0.24

	// gestione valore 4E su P0.25
	FIO0MASK = ~(1<<25);			// imposta la maschera per modificare solo il bit 25 di P0
	if(lcd_4E)
		FIO0PIN = (!lcd_BP)<<25;	// aggiorna il valore di P0.25
	else
		FIO0PIN = lcd_BP<<25;		// aggiorna il valore di P0.25

	// gestione valore 4D su P0.26
	FIO0MASK = ~(1<<26);			// imposta la maschera per modificare solo il bit 26 di P0
	if(lcd_4D)
		FIO0PIN = (!lcd_BP)<<26;	// aggiorna il valore di P0.26
	else
		FIO0PIN = lcd_BP<<26;		// aggiorna il valore di P0.26

	// gestione valore 4C su P1.30
	FIO1MASK = ~(1<<30);			// imposta la maschera per modificare solo il bit 30 di P1
	if(lcd_4C)
		FIO1PIN = (!lcd_BP)<<30;	// aggiorna il valore di P1.30
	else
		FIO1PIN = lcd_BP<<30;		// aggiorna il valore di P1.30

	// gestione valore 4B su P1.31
	FIO1MASK = ~(1<<31);			// imposta la maschera per modificare solo il bit 31 di P1
	if(lcd_4B)
		FIO1PIN = (!lcd_BP)<<31;	// aggiorna il valore di P1.31
	else
		FIO1PIN = lcd_BP<<31;		// aggiorna il valore di P1.31

	// gestione valore 4A su P0.2
	FIO0MASK = ~(1<<2);				// imposta la maschera per modificare solo il bit 2 di P0
	if(lcd_4A)
		FIO0PIN = (!lcd_BP)<<2;		// aggiorna il valore di P0.2
	else
		FIO0PIN = lcd_BP<<2;		// aggiorna il valore di P0.2

	// gestione valore 4F su P0.3
	FIO0MASK = ~(1<<3);				// imposta la maschera per modificare solo il bit 3 di P0
	if(lcd_4F)
		FIO0PIN = (!lcd_BP)<<3;		// aggiorna il valore di P0.3
	else
		FIO0PIN = lcd_BP<<3;		// aggiorna il valore di P0.3

	// gestione valore 4G su P0.21
	FIO0MASK = ~(1<<21);			// imposta la maschera per modificare solo il bit 21 di P0
	if(lcd_4G)
		FIO0PIN = (!lcd_BP)<<21;	// aggiorna il valore di P0.21
	else
		FIO0PIN = lcd_BP<<21;		// aggiorna il valore di P0.21

	// gestione valore 3B su P0.22
	FIO0MASK = ~(1<<22);			// imposta la maschera per modificare solo il bit 22 di P0
	if(lcd_3B)
		FIO0PIN = (!lcd_BP)<<22;	// aggiorna il valore di P0.22
	else
		FIO0PIN = lcd_BP<<22;		// aggiorna il valore di P0.22

	// gestione valore 3A su P0.27
	FIO0MASK = ~(1<<27);			// imposta la maschera per modificare solo il bit 27 di P0
	if(lcd_3A)
		FIO0PIN = (!lcd_BP)<<27;	// aggiorna il valore di P0.27
	else
		FIO0PIN = lcd_BP<<27;		// aggiorna il valore di P0.27

	// gestione valore 3F su P0.28
	FIO0MASK = ~(1<<28);			// imposta la maschera per modificare solo il bit 28 di P0
	if(lcd_3F)
		FIO0PIN = (!lcd_BP)<<28;	// aggiorna il valore di P0.28
	else
		FIO0PIN = lcd_BP<<28;		// aggiorna il valore di P0.28

	// gestione valore 3G su P2.13
	FIO2MASK = ~(1<<13);			// imposta la maschera per modificare solo il bit 13 di P2
	if(lcd_3G)
		FIO2PIN = (!lcd_BP)<<13;	// aggiorna il valore di P2.13
	else
		FIO2PIN = lcd_BP<<13;		// aggiorna il valore di P2.13

	// gestione valore COL su P2.12
	FIO2MASK = ~(1<<12);			// imposta la maschera per modificare solo il bit 12 di P2
	if(lcd_COL)
		FIO2PIN = (!lcd_BP)<<12;	// aggiorna il valore di P2.12
	else
		FIO2PIN = lcd_BP<<12;		// aggiorna il valore di P2.12

	// gestione valore 2B su P2.11
	FIO2MASK = ~(1<<11);			// imposta la maschera per modificare solo il bit 11 di P2
	if(lcd_2B)
		FIO2PIN = (!lcd_BP)<<11;	// aggiorna il valore di P2.11
	else
		FIO2PIN = lcd_BP<<11;		// aggiorna il valore di P2.11

	// gestione valore 2A su P2.10
	FIO2MASK = ~(1<<10);			// imposta la maschera per modificare solo il bit 10 di P2
	if(lcd_2A)
		FIO2PIN = (!lcd_BP)<<10;	// aggiorna il valore di P2.10
	else
		FIO2PIN = lcd_BP<<10;		// aggiorna il valore di P2.10

	// gestione valore 2F su P2.8
	FIO2MASK = ~(1<<8);			// imposta la maschera per modificare solo il bit 8 di P2
	if(lcd_2F)
		FIO2PIN = (!lcd_BP)<<8;	// aggiorna il valore di P2.8
	else
		FIO2PIN = lcd_BP<<8;		// aggiorna il valore di P2.8

	// gestione valore 2G su P2.7
	FIO2MASK = ~(1<<7);			// imposta la maschera per modificare solo il bit 7 di P2
	if(lcd_2G)
		FIO2PIN = (!lcd_BP)<<7;	// aggiorna il valore di P2.7
	else
		FIO2PIN = lcd_BP<<7;		// aggiorna il valore di P2.7

	// gestione valore LOBAT su P2.6
	FIO2MASK = ~(1<<6);			// imposta la maschera per modificare solo il bit 6 di P2
	if(lcd_LOBAT)
		FIO2PIN = (!lcd_BP)<<6;	// aggiorna il valore di P2.6
	else
		FIO2PIN = lcd_BP<<6;		// aggiorna il valore di P2.6

	// gestione valore TY su P2.5
	FIO2MASK = ~(1<<5);			// imposta la maschera per modificare solo il bit 5 di P2
	if(lcd_TY)
		FIO2PIN = (!lcd_BP)<<5;	// aggiorna il valore di P2.5
	else
		FIO2PIN = lcd_BP<<5;		// aggiorna il valore di P2.5


}


int main(void) {

	// Imposta GPIO P0.28, P0.27, P0.26, P0.25, P0.24, P0.23, P0.22, P0.21, P0.18,
	// P0.17, P0.16, P0.15,P0.9, P0.8, P0.7, P0.6, P0.3, P0.2, P0.1, P0.0 come output
	FIO0DIR |= 0b11111111001111000001111001111;

	// Imposta GPIO P1.31, P1.30 come output
	FIO1DIR |= 0b11000000000000000000000000000000;

	// Imposta GPIO P2.13, P2.12, P2.11, P2.10, P2.8, P2.7, P2.6, P2.5 come output
	FIO2DIR |= 0b11110111100000;

	// Impostazioni System Tick Timer
	STRELOAD = SYSTICK_VAL;		// Carica il contatore per la frequenza di aggiornamento
	STCTRL = 7;					// Abilita il Timer, il suo interrupt, con clock interno


    // Enter an infinite loop, just waiting for interrupt
    while(1) {
    	__asm volatile ("wfi");		// Wait for interrupt
    }
    return 0 ;
}
