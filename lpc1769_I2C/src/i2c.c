/*
 * i2c.c
 *
 *  Created on: 26/ott/2015
 *      Author: nicola
 */


// Function used to setup I2C1, that is P0.19 and P0.20 on LPC1769
// That's useful because an I2C-E2PROM 24LC64 is already present on evaluation board
//

#include "lpc1769.h"
#include "i2c.h"

unsigned char I2Cbuffer[I2C_BUFFER_LEN];		// I2C data buffer
unsigned char* I2CbufferPtr;					// I2C buffer pointer
int I2CbufferCnt;								// I2C buffer counter
int I2CrptStartPos;								// I2C Repeated Start position

// I2C1 Interrupt request handler
void I2C1_IRQHandler(void)
{
	unsigned int I2C_Status=0;

	I2C_Status = I2C1STAT;			// load I2C1 status register value

	switch(I2C_Status)
	{
		case START:								// START condition or
			I2CbufferPtr = I2Cbuffer;			// reset buffer pointer
		case REP_START:							// repeated START condition has been transmitted
			I2C1DAT = *I2CbufferPtr;			// load SLA+R/W to I2C1DAT
			I2CbufferCnt--;						// update buffer counter
			I2C1CONCLR = (1<<5);				// clear I2C STA flag
		break;

		////////////////////// Master transmitter mode
		case SLA_W_ACK:							// SLA+W has been transmitted; ACK has been received
		case DATA_W_ACK:						// Data byte in I2DAT has been transmitted; ACK has been received
			if(I2CbufferCnt>0)					// check buffer counter value
			{
				I2CbufferPtr++;					// update buffer pointer
				if(I2CbufferCnt!=I2CrptStartPos)
				{
					I2C1DAT = *I2CbufferPtr;	// load data byte to I2C1DAT
					I2CbufferCnt--;				// update buffer counter
				}
				else
					I2C1CONSET |= (1<<5);		// set I2C START flag (REPEATED START)
			}
			else
				I2C1CONSET = (1<<4);			// set I2C STOP flag
		break;

		case SLA_W_NACK:						// SLA+W has been transmitted; NOT ACK has been received
		case DATA_W_NACK:						// Data byte in I2DAT has been transmitted; NOT ACK has been received
			I2C1CONSET = (1<<4);				// set I2C STOP flag
		break;
		////////////////////////////////////

		////////////////////// Master receiver mode
		case SLA_R_ACK:							// SLA+R has been transmitted; ACK has been received
			I2CbufferPtr++;						// update buffer pointer
		break;

		case DATA_R_ACK:						// Data byte has been received; ACK has been returned
			if(I2CbufferCnt>1)					// check buffer counter value
				I2C1CONSET = (1<<2);			// set I2C AA flag
			else
				I2C1CONCLR = (1<<2);			// clear I2C AA flag

			*I2CbufferPtr = I2C1DAT;			// load I2C1DAT to data byte
			I2CbufferCnt--;						// update buffer counter
		break;

		case DATA_R_NACK:						// Data byte has been received; NOT ACK has been returned
			*I2CbufferPtr = I2C1DAT;			// load I2C1DAT to data byte
			I2CbufferCnt--;						// update buffer counter
		case SLA_R_NACK:						// SLA+R has been transmitted; NOT ACK has been received
			I2C1CONSET = (1<<4);				// set I2C STOP flag
		break;
		////////////////////////////////////

		case NO_RELEVANT:						// No relevant information available; SI = 0
		break;

		default:								// undefined status
			I2C1CONSET = (1<<4);				// set I2C STOP flag
	}

	I2C1CONCLR = (1<<3);						// clear I2C interrupt flag

	return;
}


// I2C1 setup function
int setupI2C1()
{
	PINSEL1 |= (0b1111 << 6);		// set bit PINSEL1[9:6] at 0b1111 so that P0.19 act as SDA1 and P0.20 as SCL1
	PINMODE1 |= (0b1010 << 6);		// set bit PINMODE1[9:6] at 0b1010 so that P0.19 and P0.20 have neither pull-up nor pull-down
	PINMODE_OD0 |= (0b11 << 19);	// set bit PINMODE_OD0[20:19] at 0b11 so that P0.19 and P0.20 are open drain

	ISER0 |= (0b1 << 11);			// set ISER0[11] so that ISE_I2C1 interrupt is enabled
	IPR2 |= (0b10000 << 27);		// set IPR2[31:27] at 0b10000 so that IP_I2C1 has priority 0x10 (middle priority)

	I2C1SCLH = I2C1SCLL = ((CORE_CLK/4)/I2C_STD_FREQ)/2;	// check equation(13) at page 457 of User Manual

	I2C1CONSET |= (1<<6);			// set I2EN to enable I2C1 interface

	return 0;
}

// I2C1 start function
int startI2C1()
{
	I2C1CONSET |= (1<<5);				// set I2C START flag

	return 0;
}

