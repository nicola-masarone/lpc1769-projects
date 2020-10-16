/*
 * lpc1769.h
 *
 *  Created on: 26/ott/2015
 *      Author: nicola
 */

#ifndef LPC1769_H_
#define LPC1769_H_


#define PINSEL1 *(volatile unsigned long*) 0x4002C004
#define PINMODE1 *(volatile unsigned long*) 0x4002C044
#define PINMODE_OD0 *(volatile unsigned long*) 0x4002C068

#define FIO0DIR *(volatile unsigned long*) 0x2009C000
#define FIO0SET *(volatile unsigned long*) 0x2009C018
#define FIO0CLR *(volatile unsigned long*) 0x2009C01C

#define PCONP *(volatile unsigned long*) 0x400FC0C4			// Power Control for Peripherals register

#define ISER0 *(volatile unsigned long*) 0xE000E100			// Interrupt Set-Enable Register 0 register
#define IPR2 *(volatile unsigned long*) 0xE000E408			// Interrupt Priority Register 2


#define CORE_CLK 96000000									// ARM core clock



#endif /* LPC1769_H_ */
