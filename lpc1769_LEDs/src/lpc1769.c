/*
===============================================================================
 Name        : lpc1769.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "board.h"


// registri GPIO
#define FIO0DIR *(volatile unsigned long*) 0x2009C000
#define FIO0SET *(volatile unsigned long*) 0x2009C018
#define FIO0CLR *(volatile unsigned long*) 0x2009C01C
#define FIO0PIN *(volatile unsigned long*) 0x2009C014

#define FIO2DIR *(volatile unsigned long*) 0x2009C040
#define FIO2SET *(volatile unsigned long*) 0x2009C058
#define FIO2CLR *(volatile unsigned long*) 0x2009C05C

#define IO0IntEnF *(volatile unsigned long*) 0x40028094
#define IO0IntClr *(volatile unsigned long*) 0x4002808C

// registri System Tick Timer
#define STCTRL *(volatile unsigned long*) 0xE000E010
#define STRELOAD *(volatile unsigned long*) 0xE000E014


// registro di abilitazione interrupt periferiche su NVIC
#define ISER0 *(volatile unsigned long*) 0xE000E100		//
#define IPR5 *(volatile unsigned long*) 0xE000E414		// registro per priorità interrupt di periferiche

// frequenza di clock del processore ARM
#define CORE_CLK 96000000

// massimo valore caricabile nel SysTick Timer (minima frequenza di lavoro)
#define SYSTICK_MAX_VAL 0xFFFFFF


// Gestore di interrupt dal timer di sistema
void SysTick_Handler(void)
{
	static int ledON = 0;
	int ledOFF;

	ledOFF = ledON-1;		// ledOFF è il LED precedente a ledON (da 0 a 7)
	if(ledOFF<0)
		ledOFF = 7;

	FIO2SET |= 1<< ledON;	// accende il LED P2.ledON
	FIO2CLR |= 1<< ledOFF;	// spegne il LED P2.ledOFF

	ledON++;
	if(ledON>7)				// ledON varia da 0 a 7
		ledON=0;
}

// Gestore di interrupt da GPIO (condiviso con ExtINT3)
void EINT3_IRQHandler (void)
{
	static int counter = 0;
	counter++;							// contatore a 3 valori: 0, 1, 2
	if(counter>2)
		counter=0;

	STCTRL &= 0xFFFFFFFE;				// disabilita System Tick Timer azzerando bit 0 di STCTRL
										// per cambiarne il valore di conteggio (periodo T)

	switch(counter)
	{
		case 0:
			STRELOAD = SYSTICK_MAX_VAL;		// Carica il contatore per la frequenza minima possibile
		break;

		case 1:
			STRELOAD = SYSTICK_MAX_VAL/2;	// Carica il contatore per il doppio della frequenza minima possibile
		break;

		case 2:
			STRELOAD = SYSTICK_MAX_VAL/4;	// Carica il contatore per il quadruplo della frequenza minima possibile
		break;

		default:
			STRELOAD = SYSTICK_MAX_VAL;		// Carica il contatore per la frequenza minima possibile
	}

	STCTRL |= 1;						// abilita System Tick Timer impostando alto il bit 0 di STCTRL
	IO0IntClr |= 1<<9;					// cancella l'interrupt di P0.9 appena gestito
}

int main(void) {

    // Imposta GPIO da P2.0 a P2.7 come output
    FIO2DIR |= 0xFF;


    // Impostazioni System Tick Timer
    STRELOAD = SYSTICK_MAX_VAL;	// Carica il contatore per la frequenza minima possibile
    STCTRL = 7;					// Abilita il Timer, il suo interrupt, con clock interno


    // Impostazioni GPIO P0.9 input con pull-up (default al Reset) e abilitazione interrupt
    IO0IntEnF |= 1<<9;		// abilita trasmissione interrupt da GPIO su fronte di discesa del pin 0.9
    IPR5 |= 0x0F<<11;		// imposta la priorità interrupt su GPIO a 0x0F (un valore intermedio)
    ISER0 |= 1<<21;			// abilita in NVIC ricezione interrupt da GPIO


    // Enter an infinite loop, just waiting for an interrupt
    while(1) {
    	__asm volatile ("wfi");		// Wait for interrupt
    }
    return 0 ;
}
