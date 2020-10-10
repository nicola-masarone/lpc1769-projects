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
char lcd_TX, lcd_1BC, lcd_DP1, lcd_2E, lcd_2D, lcd_2C, lcd_DP2, lcd_3E, lcd_3D, lcd_3C, lcd_DP3, lcd_4E, lcd_4D, lcd_4C;			// valore logici segmenti
char lcd_4B, lcd_4A, lcd_4F, lcd_4G, lcd_3B, lcd_3A, lcd_3F, lcd_3G, lcd_COL, lcd_2B, lcd_2A, lcd_2F, lcd_2G, lcd_LOBAT, lcd_TY;	// valore logici segmenti


unsigned long TimerVal=0;

// Gestore di interrupt dal timer di sistema
void SysTick_Handler(void)
{
	int val;
	static int updateCnt=FREQ_HZ;	// contatore per l'aggiornamento del dato ogni secondo (1Hz)

	updateCnt--;
	if(updateCnt==0)				// tempo di visualizzare la misura precedente e farne partire una nuova
	{
		updateCnt=FREQ_HZ;			// riparte il conteggio per la prossima lettura/visualizzazione

		val= TimerVal/58;			// converte i microsecondi in cm (con velocità del suono di 343 m/s)
		TimerVal = 0;				// il valore viene annullato per segnalare eventuale mancata lettura

		setDigit4(val%10);			// estrazione delle cifra4
		val/=10;
		setDigit3(val%10);			// estrazione delle cifra3
		val/=10;
		setDigit2(val%10);			// estrazione delle cifra2
		val/=10;
		setDigit1(val%10);			// estrazione delle cifra1

		// lancia l'impulso di 15uS
		T3TCR = 0b10;				// reset counter del Timer3, conteggio fermo
		T3EMR |= 1;					// fronte di salita su P0.10 per inizio impulso di trigger
		T3TCR = 0b01;				// avvio conteggio Timer3 (si fermerà dopo 15us con fronte di discesa su P0.10)
	}

	// gestione valore BackPlane su P0.9
	lcd_BP = !lcd_BP;				// inversione del valore logico BackPlane
	FIO0MASK = ~(1<<9);				// imposta la maschera per modificare solo il bit 9 di P0
	FIO0PIN = lcd_BP<<9;			// aggiorna il valore di P0.9

	// gestione valore TX su P0.8
	FIO0MASK = ~(1<<8);				// imposta la maschera per modificare solo il bit 8 di P0
	if(lcd_TX) FIO0PIN = (!lcd_BP)<<8; else FIO0PIN = lcd_BP<<8;	// aggiorna il valore di P0.8

	// gestione valore 1BC su P0.7
	FIO0MASK = ~(1<<7);				// imposta la maschera per modificare solo il bit 7 di P0
	if(lcd_1BC) FIO0PIN = (!lcd_BP)<<7;	else FIO0PIN = lcd_BP<<7;	// aggiorna il valore di P0.7

	// gestione valore DP1 su P0.6
	FIO0MASK = ~(1<<6);				// imposta la maschera per modificare solo il bit 6 di P0
	if(lcd_DP1) FIO0PIN = (!lcd_BP)<<6;	else FIO0PIN = lcd_BP<<6;	// aggiorna il valore di P0.6

	// gestione valore 2E su P0.0
	FIO0MASK = ~(1<<0);				// imposta la maschera per modificare solo il bit 0 di P0
	if(lcd_2E) FIO0PIN = (!lcd_BP)<<0; else FIO0PIN = lcd_BP<<0;	// aggiorna il valore di P0.0

	// gestione valore 2D su P0.1
	FIO0MASK = ~(1<<1);				// imposta la maschera per modificare solo il bit 1 di P0
	if(lcd_2D) FIO0PIN = (!lcd_BP)<<1; else FIO0PIN = lcd_BP<<1;	// aggiorna il valore di P0.1

	// gestione valore 2C su P0.18
	FIO0MASK = ~(1<<18);			// imposta la maschera per modificare solo il bit 18 di P0
	if(lcd_2C) FIO0PIN = (!lcd_BP)<<18;	else FIO0PIN = lcd_BP<<18;	// aggiorna il valore di P0.18

	// gestione valore DP2 su P0.17
	FIO0MASK = ~(1<<17);			// imposta la maschera per modificare solo il bit 17 di P0
	if(lcd_DP2) FIO0PIN = (!lcd_BP)<<17; else FIO0PIN = lcd_BP<<17;	// aggiorna il valore di P0.17

	// gestione valore 3E su P0.15
	FIO0MASK = ~(1<<15);			// imposta la maschera per modificare solo il bit 15 di P0
	if(lcd_3E) FIO0PIN = (!lcd_BP)<<15;	else FIO0PIN = lcd_BP<<15;	// aggiorna il valore di P0.15

	// gestione valore 3D su P0.16
	FIO0MASK = ~(1<<16);			// imposta la maschera per modificare solo il bit 16 di P0
	if(lcd_3D) FIO0PIN = (!lcd_BP)<<16;	else FIO0PIN = lcd_BP<<16;	// aggiorna il valore di P0.16

	// gestione valore 3C su P0.23
	FIO0MASK = ~(1<<23);			// imposta la maschera per modificare solo il bit 23 di P0
	if(lcd_3C) FIO0PIN = (!lcd_BP)<<23;	else FIO0PIN = lcd_BP<<23;	// aggiorna il valore di P0.23

	// gestione valore DP3 su P0.24
	FIO0MASK = ~(1<<24);			// imposta la maschera per modificare solo il bit 24 di P0
	if(lcd_DP3) FIO0PIN = (!lcd_BP)<<24; else FIO0PIN = lcd_BP<<24;	// aggiorna il valore di P0.24

	// gestione valore 4E su P0.25
	FIO0MASK = ~(1<<25);			// imposta la maschera per modificare solo il bit 25 di P0
	if(lcd_4E) FIO0PIN = (!lcd_BP)<<25;	else FIO0PIN = lcd_BP<<25;	// aggiorna il valore di P0.25

	// gestione valore 4D su P0.26
	FIO0MASK = ~(1<<26);			// imposta la maschera per modificare solo il bit 26 di P0
	if(lcd_4D) FIO0PIN = (!lcd_BP)<<26;	else FIO0PIN = lcd_BP<<26;	// aggiorna il valore di P0.26

	// gestione valore 4C su P1.30
	FIO1MASK = ~(1<<30);			// imposta la maschera per modificare solo il bit 30 di P1
	if(lcd_4C) FIO1PIN = (!lcd_BP)<<30;	else FIO1PIN = lcd_BP<<30;	// aggiorna il valore di P1.30

	// gestione valore 4B su P1.31
	FIO1MASK = ~(1<<31);			// imposta la maschera per modificare solo il bit 31 di P1
	if(lcd_4B) FIO1PIN = (!lcd_BP)<<31;	else FIO1PIN = lcd_BP<<31;	// aggiorna il valore di P1.31

	// gestione valore 4A su P0.2
	FIO0MASK = ~(1<<2);				// imposta la maschera per modificare solo il bit 2 di P0
	if(lcd_4A) FIO0PIN = (!lcd_BP)<<2; else FIO0PIN = lcd_BP<<2;	// aggiorna il valore di P0.2

	// gestione valore 4F su P0.3
	FIO0MASK = ~(1<<3);				// imposta la maschera per modificare solo il bit 3 di P0
	if(lcd_4F) FIO0PIN = (!lcd_BP)<<3; else FIO0PIN = lcd_BP<<3;	// aggiorna il valore di P0.3

	// gestione valore 4G su P0.21
	FIO0MASK = ~(1<<21);			// imposta la maschera per modificare solo il bit 21 di P0
	if(lcd_4G) FIO0PIN = (!lcd_BP)<<21;	else FIO0PIN = lcd_BP<<21;	// aggiorna il valore di P0.21

	// gestione valore 3B su P0.22
	FIO0MASK = ~(1<<22);			// imposta la maschera per modificare solo il bit 22 di P0
	if(lcd_3B) FIO0PIN = (!lcd_BP)<<22;	else FIO0PIN = lcd_BP<<22;	// aggiorna il valore di P0.22

	// gestione valore 3A su P0.27
	FIO0MASK = ~(1<<27);			// imposta la maschera per modificare solo il bit 27 di P0
	if(lcd_3A) FIO0PIN = (!lcd_BP)<<27;	else FIO0PIN = lcd_BP<<27;	// aggiorna il valore di P0.27

	// gestione valore 3F su P0.28
	FIO0MASK = ~(1<<28);			// imposta la maschera per modificare solo il bit 28 di P0
	if(lcd_3F) FIO0PIN = (!lcd_BP)<<28;	else FIO0PIN = lcd_BP<<28;	// aggiorna il valore di P0.28

	// gestione valore 3G su P2.13
	FIO2MASK = ~(1<<13);			// imposta la maschera per modificare solo il bit 13 di P2
	if(lcd_3G) FIO2PIN = (!lcd_BP)<<13;	else FIO2PIN = lcd_BP<<13;	// aggiorna il valore di P2.13

	// gestione valore COL su P2.12
	FIO2MASK = ~(1<<12);			// imposta la maschera per modificare solo il bit 12 di P2
	if(lcd_COL) FIO2PIN = (!lcd_BP)<<12; else FIO2PIN = lcd_BP<<12;	// aggiorna il valore di P2.12

	// gestione valore 2B su P2.11
	FIO2MASK = ~(1<<11);			// imposta la maschera per modificare solo il bit 11 di P2
	if(lcd_2B) FIO2PIN = (!lcd_BP)<<11;	else FIO2PIN = lcd_BP<<11;	// aggiorna il valore di P2.11

	// gestione valore 2A su P2.10
	FIO2MASK = ~(1<<10);			// imposta la maschera per modificare solo il bit 10 di P2
	if(lcd_2A) FIO2PIN = (!lcd_BP)<<10;	else FIO2PIN = lcd_BP<<10;	// aggiorna il valore di P2.10

	// gestione valore 2F su P2.8
	FIO2MASK = ~(1<<8);			// imposta la maschera per modificare solo il bit 8 di P2
	if(lcd_2F) FIO2PIN = (!lcd_BP)<<8; else FIO2PIN = lcd_BP<<8;	// aggiorna il valore di P2.8

	// gestione valore 2G su P2.7
	FIO2MASK = ~(1<<7);			// imposta la maschera per modificare solo il bit 7 di P2
	if(lcd_2G) FIO2PIN = (!lcd_BP)<<7; else FIO2PIN = lcd_BP<<7;	// aggiorna il valore di P2.7

	// gestione valore LOBAT su P2.6
	FIO2MASK = ~(1<<6);			// imposta la maschera per modificare solo il bit 6 di P2
	if(lcd_LOBAT) FIO2PIN = (!lcd_BP)<<6; else FIO2PIN = lcd_BP<<6;	// aggiorna il valore di P2.6

	// gestione valore TY su P2.5
	FIO2MASK = ~(1<<5);			// imposta la maschera per modificare solo il bit 5 di P2
	if(lcd_TY) FIO2PIN = (!lcd_BP)<<5; else FIO2PIN = lcd_BP<<5;	// aggiorna il valore di P2.5
}


void TIMER2_IRQHandler(void)
{
	FIO0MASK = 0;
	if(FIO0PIN & (1<<4))
	{	// interrupt per fronte di salita su P0.4
		T2TCR = 0b10;					// ferma il TIMER2 e lo azzera (reset)
		T2TCR = 0b01;					// avvia il TIMER2
	}
	else
	{	// interrupt per fronte di discesa su P0.4
		T2TCR = 0b00;								// ferma il TIMER2
		TimerVal = T2CR0/((CORE_CLK/4)/1000000);	// calcola il tempo trascorso in microsecondi
		// riesce a misurare fino a quasi 3 minuti di durata
	}
	T2IR = 1<<4;			// reset dell'interrupt su CR0 di TIMER2
}



// Inizializza Timer2 come Capture su P0.4
void initTimer2Capture(void)
{
	PCONP |= 1<<22; 		// PCTIM2=1 alimentazione TIMER2 ON
	// PCLKSEL1 |= 0b00<<12;// ridondante, a RESET è già impostato a 00, PCLK_peripheral = CCLK/4
	PINSEL0 |= (0b11<<8);	// abilita la funzionalità CAP2.0 (capture Timer2, canale0) su P0.4
	PINMODE0 |= (0b10<<8);	// disabilita su P0.4 i resistori interni di pull-up e pull-down
	T2CCR = 0b000111;		// abilita caricamento di CR0 con valore TIMER2 e genera interrupt su fronte di salita e discesa
	ISER0 = (1<<3);			// abilita gestione interrupt TIMER2 su NVIC
}

// Inizializza Timer3 come Match su P0.10
void initTimer3Match(void)
{
	PCONP |= 1<<23; 		// PCTIM3=1 alimentazione TIMER3 ON
	// PCLKSEL1 |= 0b00<<12;// ridondante, a RESET è già impostato a 00, PCLK_peripheral = CCLK/4
	PINSEL0 |= (0b11<<20);	// abilita la funzionalità MAT3.0 (match Timer3, canale0) su P0.10
	PINMODE0 |= (0b10<<20);	// disabilita su P0.10 i resistori interni di pull-up e pull-down
	PINMODE_OD0 |= (1<<10);	// imposta P0.10 come OpenDrain, permettendo l'utilizzo a 5V con pull-up e alimentazione esterni

	T3MCR |= (1<<2);		// imposta l'arresto di Timer3 su match MR0
	T3EMR |= (0b01<<4);		// imposta P0.10 al valore basso quando il Timer3 raggiunge il valore previsto (EMC0=01)
	T3MR0 = ((CORE_CLK/4)/1E6)*15;	// il match avviene dopo 15us (durata dell'impulso di trigger)
	//T3MR0 = (CORE_CLK/4)/10;// TEST **** il match avviene dopo 0.1s (durata dell'impulso di trigger) TEST **** TEST ****
	T3EMR &= 0b11111111110;	// livello iniziale basso su P0.10 (trigger)
}




int main(void) {

	// Impostazioni System Tick Timer
	STRELOAD = SYSTICK_VAL;			// Carica il contatore per la frequenza di aggiornamento
	STCTRL = 7;						// Abilita il Timer, il suo interrupt, con clock interno

	initTimer3Match();				// Inizializza Timer3 come Match su P0.10
    initTimer2Capture();			// Inizializza Timer2 come Capture su P0.4
    initLCD();						// Inizializza le linee di gestione LCD

    // Enter an infinite loop, just waiting for interrupt
    while(1) {
    	__asm volatile ("wfi");		// Wait for interrupt
    }
    return 0 ;
}
