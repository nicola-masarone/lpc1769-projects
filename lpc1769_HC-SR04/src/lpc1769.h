/*
 * lpc1769.h
 *
 *  Created on: 20/mar/2015
 *      Author: nicola
 */

#ifndef LPC1769_H_
#define LPC1769_H_

#define PCONP *(volatile unsigned long*) 0x400FC0C4
#define PCLKSEL1 *(volatile unsigned long*) 0x400FC1AC
#define PINSEL0 *(volatile unsigned long*) 0x4002C000
#define PINMODE0 *(volatile unsigned long*) 0x4002C040
#define PINMODE_OD0 *(volatile unsigned long*) 0x4002C068
#define ISER0 *(volatile unsigned long*) 0xE000E100

#define T2CCR *(volatile unsigned long*) 0x40090028
#define T2TCR *(volatile unsigned long*) 0x40090004
#define T2CR0 *(volatile unsigned long*) 0x4009002C
#define T2IR *(volatile unsigned long*) 0x40090000

#define T3TCR *(volatile unsigned long*) 0x40094004
#define T3MCR *(volatile unsigned long*) 0x40094014
#define T3EMR *(volatile unsigned long*) 0x4009403C
#define T3MR0 *(volatile unsigned long*) 0x40094018

// frequenza di clock del processore ARM
#define CORE_CLK 96000000

#define FIO0DIR *(volatile unsigned long*) 0x2009C000
#define FIO0SET *(volatile unsigned long*) 0x2009C018
#define FIO0CLR *(volatile unsigned long*) 0x2009C01C


#define FIO0DIR *(volatile unsigned long*) 0x2009C000
#define FIO0PIN *(volatile unsigned long*) 0x2009C014
#define FIO0MASK *(volatile unsigned long*) 0x2009C010

#define FIO1DIR *(volatile unsigned long*) 0x2009C020
#define FIO1PIN *(volatile unsigned long*) 0x2009C034
#define FIO1MASK *(volatile unsigned long*) 0x2009C030

#define FIO2DIR *(volatile unsigned long*) 0x2009C040
#define FIO2PIN *(volatile unsigned long*) 0x2009C054
#define FIO2MASK *(volatile unsigned long*) 0x2009C050


// registri System Tick Timer
#define STCTRL *(volatile unsigned long*) 0xE000E010
#define STRELOAD *(volatile unsigned long*) 0xE000E014

// frequenza di clock del processore ARM
#define CORE_CLK 96000000

// carica in SysTick Timer il valore di semi-aggiornamento LCD
#define FREQ_HZ 64								// 64 Hz per la semionda, 32 Hz per l'onda intera
#define SYSTICK_VAL CORE_CLK/FREQ_HZ - 1		// valore per il Timer di SysTick



#endif /* LPC1769_H_ */
