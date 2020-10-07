/*
 * lpc1769.h
 *
 *  Created on: 20/mar/2015
 *      Author: nicola
 */

#ifndef LPC1769_H_
#define LPC1769_H_


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
#define SYSTICK_VAL CORE_CLK/64	- 1		// 64 Hz per la semionda, 32 Hz per l'onda intera



#endif /* LPC1769_H_ */
