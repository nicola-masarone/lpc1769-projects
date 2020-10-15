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

#define FIO0PIN *(volatile unsigned long*) 0x2009C014
#define FIO0DIR *(volatile unsigned long*) 0x2009C000
#define FIO0CLR *(volatile unsigned long*) 0x2009C01C
#define FIO0SET  *(volatile unsigned long*) 0x2009C018

#define IO0IntEnR *(volatile unsigned long*) 0x40028090
#define IO0IntEnF *(volatile unsigned long*) 0x40028094
#define IO0IntClr *(volatile unsigned long*) 0x4002808C

#define PCONP *(volatile unsigned long*) 0x400FC0C4
#define PCLKSEL1 *(volatile unsigned long*) 0x400FC1AC
#define PINSEL0 *(volatile unsigned long*) 0x4002C000
#define PINMODE0 *(volatile unsigned long*) 0x4002C040
#define ISER0 *(volatile unsigned long*) 0xE000E100
#define ICER0 *(volatile unsigned long*) 0xE000E180

#define T2CCR *(volatile unsigned long*) 0x40090028
#define T2TCR *(volatile unsigned long*) 0x40090004
#define T2CR0 *(volatile unsigned long*) 0x4009002C
#define T2IR *(volatile unsigned long*) 0x40090000
#define T2MR0 *(volatile unsigned long*) 0x40090018
#define T2MCR *(volatile unsigned long*) 0x40090014

// frequenza di clock del processore ARM
#define CORE_CLK 96000000

unsigned char RH_int, RH_dec, T_int, T_dec, checksum;
unsigned long TimerVal_us, checksumErrCounter=0;
unsigned char delayCompleted=0, DHT11Ready=0, newBitReady=0;

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
	static int time_counter=0, hum_temp=0;
	int val, int_val, dec_val;

	time_counter++;

	if(time_counter>256)
	{
		time_counter=0;

		if(hum_temp)
		{
			int_val = RH_int;
			dec_val = RH_dec;
			lcd_TY = 1;
		}
		else
		{
			int_val = T_int;
			dec_val = T_dec;
			lcd_TY = 0;
		}

		setDP3(1);
		setDigit4(dec_val);
		val=int_val;
		setDigit3(val%10);
		val/=10;
		setDigit2(val%10);
		val/=10;
		setDigit1(val%10);

		hum_temp = !hum_temp;	// inverte la grandezza da visualizzare
	}

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


// Gestore di interrupt da GPIO (condiviso con ExtINT3)
void EINT3_IRQHandler (void)
{
	DHT11Ready = 1;										// DHT11 ha risposto con un impulso comprendente un fronte di salita
	IO0IntClr |= 1<<4;									// reset interrupt da P0.4
}

void TIMER2_IRQHandler(void)
{
	// verifica interrupt causato da CR0
	if(T2IR&(1<<4))
	{
		FIO0MASK = ~(1<<4);								// imposta la maschera per accedere al bit 4 di P0

		if(FIO0PIN & (1<<4))							// scattato interrupt per fronte di salita su P0.4
		{
			T2TCR = 0b10;								// ferma il TIMER2 e lo azzera
			T2CCR = 0b000110;							// abilita il successivo caricamento di CR0 su fronte di discesa con generazione di interrupt
			T2TCR = 0b01;								// avvia il TIMER2
		}
		else											// scattato interrupt per fronte di discesa su P0.4
		{
			T2TCR = 0b00;								// ferma il TIMER2
			T2CCR = 0b000101;							// abilita il successivo caricamento di CR0 su fronte di salita con generazione di interrupt
			TimerVal_us = T2CR0/((CORE_CLK/4)/1000000);	// calcola il tempo trascorso in microsecondi
			newBitReady = 1;							// ricevuto nuovo bit
		}
		T2IR |= 1<<4;									// reset dell'interrupt su CR0 di TIMER2
	}

	// verifica interrupt causato da MR0
	if(T2IR&1)
	{
		delayCompleted = 1;							// impostazione della flag delayCompleted
		T2IR |= 1;									// reset dell'interrupt su MR0 di TIMER2
	}

}

void setDelayms(unsigned int ms)
{
	T2TCR = 0b10;									// ferma il TIMER2 e lo azzera
	T2MR0 = ((CORE_CLK/4)/1000)*ms;					// imposta MR0 per un ritardo ms
	T2MCR = 0b111;									// interrupt, reset e stop di Timer2 quando raggiunge il valore T2MR0
	ISER0 = 1<<3;									// abilita in NVIC ricezione interrupt da TIMER2
	T2TCR = 0b01;									// avvia il TIMER2
}


int main(void)
{
	int status = 0, bit;
	unsigned char buf[40];

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

	PCONP |= 1<<22; 								// PCTIM2=1 alimentazione TIMER2 ON

	// Attesa per il reset DHT11
	delayCompleted = 0;								// reset della flag delayCompleted
	setDelayms(2000);
	do
	{
		__asm volatile ("wfi");						// aspetta qualsiasi interrupt
	}while(!delayCompleted);						// controlla la flag delayCompleted
	delayCompleted = 0;								// reset della flag delayCompleted

    while(1)										// ciclo principale del programma microcontrollore
    {
    	switch(status)
    	{
    		// inizio segnale di start dal uC al sensore DHT11
    		case 0:
    			ICER0 = (1<<3);						// disabilita in NVIC ricezione interrupt da TIMER2
    			PINSEL0 &= ~(0b11<<8);				// abilita la funzionalità GPIO su P0.4
    			FIO0MASK = ~(1<<4);					// imposta la maschera per modificare solo il bit 4 di P0
    			FIO0DIR |= (1<<4);					// imposta P0.4 come output
    			FIO0CLR |= (1<<4);					// livello basso su P0.4

    			delayCompleted = 0;					// reset della flag delayCompleted
    			setDelayms(20);
    			do
    			{
    				__asm volatile ("wfi");			// aspetta qualsiasi interrupt
    			}while(!delayCompleted);			// controlla la flag delayCompleted
    			delayCompleted = 0;					// reset della flag delayCompleted

    			status = 1;							// imposta il prossimo stato (sarà raggiunto al risveglio dopo il ritardo impostato)
    		break;

    		// fine segnale di start dal uC al sensore DHT11
    		case 1:
    			ICER0 = (1<<3);						// disabilita in NVIC ricezione interrupt da TIMER2
    			FIO0MASK = ~(1<<4);					// imposta la maschera per modificare solo il bit 4 di P0
    			FIO0SET |= (1<<4);					// livello alto su P0.4
    			FIO0DIR &= ~(1<<4);					// imposta P0.4 come input (va a livello alto per pull-up)
    			IO0IntEnR |= (1<<4);				// abilità P0.4 come sorgente di interrupt su fronte di salita
    			ISER0 |= (1<<21);					// abilita in NVIC ricezione interrupt da GPIO

    			DHT11Ready = 0;						// reset della flag DHT11Ready
    			do
    			{
    				__asm volatile ("wfi");			// attende qualsiasi interrupt
    			}while(!DHT11Ready);				// controlla la flag DHT11Ready
    			DHT11Ready = 0;						// reset della flag DHT11Ready

    			status = 2;							// imposta il prossimo stato (sarà raggiunto dopo l'interrupt per il fronte di salita)
    		break;

    		// DHT11 pronto a trasmettere il primo bit
    		case 2:
    			IO0IntEnR &= ~(1<<4);				// disabilita P0.4 come sorgente di interrupt su fronte di salita
    			ICER0 |= (1<<21);					// disabilita in NVIC ricezione interrupt da GPIO
    			PINSEL0 |= 0b11<<8;					// abilita la funzionalità CAP2.0 (capture Timer2, canale0) su P0.4 (diventa input automaticamente)
    			T2CCR = 0b000101;					// abilita caricamento di CR0 su fronte di salita con generazione di interrupt
    			ISER0 = (1<<3);						// abilita gestione interrupt TIMER2 su NVIC
    			bit = 39;							// prossimo bit ricevuto sarà il 39°
    			status = 3;
    		break;

    		// gestione del buffer da 40 bit ricevuto da DHT11
    		case 3:
    			newBitReady = 0;					// reset della flag newBitReady
    			do
    			{
    				__asm volatile ("wfi");			// attende qualsiasi interrupt
    			}while(!newBitReady);				// controlla la flag newBitReady
    			newBitReady = 0;					// reset della flag newBitReady

				buf[bit] = (TimerVal_us>50);

				if(bit)
					bit--;
				else
				{
					T2TCR = 0b10;				// ferma il TIMER2 e lo azzera
					T2CCR = 0;					// disabilita totalmente CR0

					int i, j;
					RH_int = RH_dec = T_int = T_dec = checksum = 0;
					// Estrazione valori RH_int, RH_dec, T_int, T_dec, checksum
					for(i=39, j=7; j>=0; i--, j--)
						RH_int |= (buf[i]<<j);

					for(i=31, j=7; j>=0; i--, j--)
						RH_dec |= (buf[i]<<j);
					for(i=23, j=7; j>=0; i--, j--)
						T_int |= (buf[i]<<j);
					for(i=15, j=7; j>=0; i--, j--)
						T_dec |= (buf[i]<<j);
					for(i=7, j=7; j>=0; i--, j--)
						checksum |= (buf[i]<<j);

					// verifica checksum
					if((RH_int + RH_dec + T_int + T_dec)!=checksum)
						checksumErrCounter++;

	    			delayCompleted = 0;					// reset della flag delayCompleted
					setDelayms(2000);			// ritardo di 2s prima della prossima lettura
	    			do
	    			{
	    				__asm volatile ("wfi");			// aspetta qualsiasi interrupt
	    			}while(!delayCompleted);			// controlla la flag delayCompleted
	    			delayCompleted = 0;					// reset della flag delayCompleted

					status = 0;					// imposta il prossimo stato (sarà raggiunto al risveglio dopo il ritardo impostato)
				}
    		break;

    		default:
    			status = 0;
    	}
    }
    return 0 ;
}
