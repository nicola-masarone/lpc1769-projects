/*
 * lcd.c
 *
 *  Created on: 20/mar/2015
 *      Author: nicola
 */
#include "lcd.h"
#include "lpc1769.h"

extern char lcd_TX, lcd_1BC, lcd_DP1, lcd_2E, lcd_2D, lcd_2C, lcd_DP2, lcd_3E, lcd_3D, lcd_3C, lcd_DP3, lcd_4E, lcd_4D, lcd_4C;			// valore logici segmenti
extern char lcd_4B, lcd_4A, lcd_4F, lcd_4G, lcd_3B, lcd_3A, lcd_3F, lcd_3G, lcd_COL, lcd_2B, lcd_2A, lcd_2F, lcd_2G, lcd_LOBAT, lcd_TY;	// valore logici segmenti

// inizializzazione linee LCD
void initLCD(void)
{
	// Imposta GPIO P0.28, P0.27, P0.26, P0.25, P0.24, P0.23, P0.22, P0.21, P0.18,
	// P0.17, P0.16, P0.15,P0.9, P0.8, P0.7, P0.6, P0.3, P0.2, P0.1, P0.0 come output
	FIO0DIR |= 0b11111111001111000001111001111;

	// Imposta GPIO P1.31, P1.30 come output
	FIO1DIR |= 0b11000000000000000000000000000000;

	// Imposta GPIO P2.13, P2.12, P2.11, P2.10, P2.8, P2.7, P2.6, P2.5 come output
	FIO2DIR |= 0b11110111100000;
}


// funzione di gestione della cifra 1
void setDigit1(int val)
{
	if(val)
		lcd_1BC = 1;
	else
		lcd_1BC = 0;

	return;
}

// funzione di gestione della cifra 2
void setDigit2(int val)
{
	switch(val)
	{
		case 0:				// valore 0
			lcd_2A = 1;
			lcd_2B = 1;
			lcd_2C = 1;
			lcd_2D = 1;
			lcd_2E = 1;
			lcd_2F = 1;
			lcd_2G = 0;
		break;
		case 1:				// valore 1
			lcd_2A = 0;
			lcd_2B = 1;
			lcd_2C = 1;
			lcd_2D = 0;
			lcd_2E = 0;
			lcd_2F = 0;
			lcd_2G = 0;

		break;
		case 2:				// valore 2
			lcd_2A = 1;
			lcd_2B = 1;
			lcd_2C = 0;
			lcd_2D = 1;
			lcd_2E = 1;
			lcd_2F = 0;
			lcd_2G = 1;
		break;
		case 3:				// valore 3
			lcd_2A = 1;
			lcd_2B = 1;
			lcd_2C = 1;
			lcd_2D = 1;
			lcd_2E = 0;
			lcd_2F = 0;
			lcd_2G = 1;
		break;
		case 4:				// valore 4
			lcd_2A = 0;
			lcd_2B = 1;
			lcd_2C = 1;
			lcd_2D = 0;
			lcd_2E = 0;
			lcd_2F = 1;
			lcd_2G = 1;
		break;
		case 5:				// valore 5
			lcd_2A = 1;
			lcd_2B = 0;
			lcd_2C = 1;
			lcd_2D = 1;
			lcd_2E = 0;
			lcd_2F = 1;
			lcd_2G = 1;
		break;
		case 6:				// valore 6
			lcd_2A = 1;
			lcd_2B = 0;
			lcd_2C = 1;
			lcd_2D = 1;
			lcd_2E = 1;
			lcd_2F = 1;
			lcd_2G = 1;
		break;
		case 7:				// valore 7
			lcd_2A = 1;
			lcd_2B = 1;
			lcd_2C = 1;
			lcd_2D = 0;
			lcd_2E = 0;
			lcd_2F = 0;
			lcd_2G = 0;
		break;
		case 8:				// valore 8
			lcd_2A = 1;
			lcd_2B = 1;
			lcd_2C = 1;
			lcd_2D = 1;
			lcd_2E = 1;
			lcd_2F = 1;
			lcd_2G = 1;
		break;
		case 9:				// valore 9
			lcd_2A = 1;
			lcd_2B = 1;
			lcd_2C = 1;
			lcd_2D = 1;
			lcd_2E = 0;
			lcd_2F = 1;
			lcd_2G = 1;
		break;
		default:			// valore sconosciuto: spegnimento cifra
			lcd_2A = 0;
			lcd_2B = 0;
			lcd_2C = 0;
			lcd_2D = 0;
			lcd_2E = 0;
			lcd_2F = 0;
			lcd_2G = 0;
	}

	return;
}


// funzione di gestione della cifra 3
void setDigit3(int val)
{
	switch(val)
	{
		case 0:				// valore 0
			lcd_3A = 1;
			lcd_3B = 1;
			lcd_3C = 1;
			lcd_3D = 1;
			lcd_3E = 1;
			lcd_3F = 1;
			lcd_3G = 0;
		break;
		case 1:				// valore 1
			lcd_3A = 0;
			lcd_3B = 1;
			lcd_3C = 1;
			lcd_3D = 0;
			lcd_3E = 0;
			lcd_3F = 0;
			lcd_3G = 0;

		break;
		case 2:				// valore 2
			lcd_3A = 1;
			lcd_3B = 1;
			lcd_3C = 0;
			lcd_3D = 1;
			lcd_3E = 1;
			lcd_3F = 0;
			lcd_3G = 1;
		break;
		case 3:				// valore 3
			lcd_3A = 1;
			lcd_3B = 1;
			lcd_3C = 1;
			lcd_3D = 1;
			lcd_3E = 0;
			lcd_3F = 0;
			lcd_3G = 1;
		break;
		case 4:				// valore 4
			lcd_3A = 0;
			lcd_3B = 1;
			lcd_3C = 1;
			lcd_3D = 0;
			lcd_3E = 0;
			lcd_3F = 1;
			lcd_3G = 1;
		break;
		case 5:				// valore 5
			lcd_3A = 1;
			lcd_3B = 0;
			lcd_3C = 1;
			lcd_3D = 1;
			lcd_3E = 0;
			lcd_3F = 1;
			lcd_3G = 1;
		break;
		case 6:				// valore 6
			lcd_3A = 1;
			lcd_3B = 0;
			lcd_3C = 1;
			lcd_3D = 1;
			lcd_3E = 1;
			lcd_3F = 1;
			lcd_3G = 1;
		break;
		case 7:				// valore 7
			lcd_3A = 1;
			lcd_3B = 1;
			lcd_3C = 1;
			lcd_3D = 0;
			lcd_3E = 0;
			lcd_3F = 0;
			lcd_3G = 0;
		break;
		case 8:				// valore 8
			lcd_3A = 1;
			lcd_3B = 1;
			lcd_3C = 1;
			lcd_3D = 1;
			lcd_3E = 1;
			lcd_3F = 1;
			lcd_3G = 1;
		break;
		case 9:				// valore 9
			lcd_3A = 1;
			lcd_3B = 1;
			lcd_3C = 1;
			lcd_3D = 1;
			lcd_3E = 0;
			lcd_3F = 1;
			lcd_3G = 1;
		break;
		default:			// valore sconosciuto: spegnimento cifra
			lcd_3A = 0;
			lcd_3B = 0;
			lcd_3C = 0;
			lcd_3D = 0;
			lcd_3E = 0;
			lcd_3F = 0;
			lcd_3G = 0;
	}

	return;
}


// funzione di gestione della cifra 4
void setDigit4(int val)
{
	switch(val)
	{
		case 0:				// valore 0
			lcd_4A = 1;
			lcd_4B = 1;
			lcd_4C = 1;
			lcd_4D = 1;
			lcd_4E = 1;
			lcd_4F = 1;
			lcd_4G = 0;
		break;
		case 1:				// valore 1
			lcd_4A = 0;
			lcd_4B = 1;
			lcd_4C = 1;
			lcd_4D = 0;
			lcd_4E = 0;
			lcd_4F = 0;
			lcd_4G = 0;

		break;
		case 2:				// valore 2
			lcd_4A = 1;
			lcd_4B = 1;
			lcd_4C = 0;
			lcd_4D = 1;
			lcd_4E = 1;
			lcd_4F = 0;
			lcd_4G = 1;
		break;
		case 3:				// valore 3
			lcd_4A = 1;
			lcd_4B = 1;
			lcd_4C = 1;
			lcd_4D = 1;
			lcd_4E = 0;
			lcd_4F = 0;
			lcd_4G = 1;
		break;
		case 4:				// valore 4
			lcd_4A = 0;
			lcd_4B = 1;
			lcd_4C = 1;
			lcd_4D = 0;
			lcd_4E = 0;
			lcd_4F = 1;
			lcd_4G = 1;
		break;
		case 5:				// valore 5
			lcd_4A = 1;
			lcd_4B = 0;
			lcd_4C = 1;
			lcd_4D = 1;
			lcd_4E = 0;
			lcd_4F = 1;
			lcd_4G = 1;
		break;
		case 6:				// valore 6
			lcd_4A = 1;
			lcd_4B = 0;
			lcd_4C = 1;
			lcd_4D = 1;
			lcd_4E = 1;
			lcd_4F = 1;
			lcd_4G = 1;
		break;
		case 7:				// valore 7
			lcd_4A = 1;
			lcd_4B = 1;
			lcd_4C = 1;
			lcd_4D = 0;
			lcd_4E = 0;
			lcd_4F = 0;
			lcd_4G = 0;
		break;
		case 8:				// valore 8
			lcd_4A = 1;
			lcd_4B = 1;
			lcd_4C = 1;
			lcd_4D = 1;
			lcd_4E = 1;
			lcd_4F = 1;
			lcd_4G = 1;
		break;
		case 9:				// valore 9
			lcd_4A = 1;
			lcd_4B = 1;
			lcd_4C = 1;
			lcd_4D = 1;
			lcd_4E = 0;
			lcd_4F = 1;
			lcd_4G = 1;
		break;
		default:			// valore sconosciuto: spegnimento cifra
			lcd_4A = 0;
			lcd_4B = 0;
			lcd_4C = 0;
			lcd_4D = 0;
			lcd_4E = 0;
			lcd_4F = 0;
			lcd_4G = 0;
	}

	return;
}


void setDP1(int val)
{
	if(val)
		lcd_DP1 = 1;
	else
		lcd_DP1 = 0;
	return;
}

void setDP2(int val)
{
	if(val)
		lcd_DP2 = 1;
	else
		lcd_DP2 = 0;
	return;
}

void setDP3(int val)
{
	if(val)
		lcd_DP3 = 1;
	else
		lcd_DP3 = 0;
	return;
}

void setCOL(int val)
{
	if(val)
		lcd_COL = 1;
	else
		lcd_COL = 0;
	return;
}

void setSign(int val)
{
	if(val>0)
	{
		lcd_TX = 1;
		lcd_TY = 1;
	}
	else if(val<0)
	{
		lcd_TX = 1;
		lcd_TY = 0;
	}
	else
	{
		lcd_TX = 0;
		lcd_TY = 0;
	}


	return;
}

void setLoBat(int val)
{
	if(val)
		lcd_LOBAT = 1;
	else
		lcd_LOBAT = 0;
	return;
}
