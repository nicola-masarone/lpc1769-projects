/*
 * lcd.c
 *
 *  Created on: 20/mar/2015
 *      Author: nicola
 */
#include "lcd.h"
#include "lpc1769.h"

extern char lcd_TX;		// valore logico TX
extern char lcd_1BC;	// valore logico 1BC
extern char lcd_DP1;	// valore logico DP1
extern char lcd_2E;		// valore logico 2E
extern char lcd_2D;		// valore logico 2D
extern char lcd_2C;		// valore logico 2C
extern char lcd_DP2;	// valore logico DP2
extern char lcd_3E;		// valore logico 3E
extern char lcd_3D;		// valore logico 3D
extern char lcd_3C;		// valore logico 3C
extern char lcd_DP3;		// valore logico DP3
extern char lcd_4E;		// valore logico 4E
extern char lcd_4D;		// valore logico 4D
extern char lcd_4C;		// valore logico 4C
extern char lcd_4B;		// valore logico 4B
extern char lcd_4A;		// valore logico 4A
extern char lcd_4F;		// valore logico 4F
extern char lcd_4G;		// valore logico 4G
extern char lcd_3B;		// valore logico 3B
extern char lcd_3A;		// valore logico 3A
extern char lcd_3F;		// valore logico 3F
extern char lcd_3G;		// valore logico 3G
extern char lcd_COL;	// valore logico COL
extern char lcd_2B;		// valore logico 2B
extern char lcd_2A;		// valore logico 2A
extern char lcd_2F;		// valore logico 2F
extern char lcd_2G;		// valore logico 2G
extern char lcd_LOBAT;	// valore logico LOBAT
extern char lcd_TY;		// valore logico TY

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
