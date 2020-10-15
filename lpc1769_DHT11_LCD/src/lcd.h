/*
 * lcd.h
 *
 *  Created on: 20/mar/2015
 *      Author: nicola
 */

#ifndef LCD_H_
#define LCD_H_

void setDigit1(int val);	// funzione di gestione della cifra 1
void setDigit2(int val);	// funzione di gestione della cifra 2
void setDigit3(int val);	// funzione di gestione della cifra 3
void setDigit4(int val);	// funzione di gestione della cifra 4

void setDP1(int val);		// funzione di gestione del punto decimale 1
void setDP2(int val);		// funzione di gestione del punto decimale 2
void setDP3(int val);		// funzione di gestione del punto decimale 3

void setCOL(int val);		// funzione di gestione dei due punti

void setSign(int val);		// funzione di gestione del segno + , -

void setLoBat(int val);		// funzione di gestione del segnale di batteria scarica

#endif /* LCD_H_ */
