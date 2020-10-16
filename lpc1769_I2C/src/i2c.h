/*
 * i2c.h
 *
 *  Created on: 26/ott/2015
 *      Author: nicola
 */

#ifndef I2C_H_
#define I2C_H_

#define I2C_STD_FREQ	100000								// I2C standard frequency 100kHz

#define I2C1SCLH *(volatile unsigned long*) 0x4005C010		// I2C1 SCL HIGH duty cycle register
#define I2C1SCLL *(volatile unsigned long*) 0x4005C014		// I2C1 SCL Low duty cycle register
#define I2C1STAT *(volatile unsigned long*) 0x4005C004		// I2C1 Status register
#define I2C1DAT *(volatile unsigned long*) 0x4005C008		// I2C1 Data register
#define I2C1CONSET *(volatile unsigned long*) 0x4005C000	// I2C1 Control Set register
#define I2C1CONCLR *(volatile unsigned long*) 0x4005C018	// I2C1 Control Clear register

#define I2C_BUFFER_LEN	64									// I2C buffer length

// I2C status codes
#define START			0x08			// a START condition has been transmitted
#define REP_START		0x10			// a repeated START condition has been transmitted
#define SLA_W_ACK		0x18			// SLA+W has been transmitted; ACK has been received
#define SLA_W_NACK		0x20			// SLA+W has been transmitted; NOT ACK has been received
#define DATA_W_ACK		0x28			// Data byte in I2DAT has been transmitted; ACK has been received
#define DATA_W_NACK		0x30			// Data byte in I2DAT has been transmitted; NOT ACK has been received
#define SLA_R_ACK		0x40			// SLA+R has been transmitted; ACK has been received
#define SLA_R_NACK		0x48			// SLA+R has been transmitted; NOT ACK has been received
#define DATA_R_ACK		0x50			// Data byte has been received; ACK has been returned
#define DATA_R_NACK		0x58			// Data byte has been received; NOT ACK has been returned

#define NO_RELEVANT		0xF8			// No relevant information available; SI = 0


int setupI2C1();
int startI2C1();


// 24LC64 defines
#define ADDR_24LC64_W	0b10100000		// 24LC64 address for write operation
#define ADDR_24LC64_R	0b10100001		// 24LC64 address for write operation

// MAX7300 defines
#define ADDR_MAX7300_W				0b10000000	// MAX7300 address for write operation
#define ADDR_MAX7300_R				0b10000001	// MAX7300 address for write operation
#define MAX7300_CFG_REG 			0x04		// MAX7300 configuration register
#define MAX7300_P20_P23_CFG_REG 	0x0D		// MAX7300 P20 to P23 configuration register
#define MAX7300_P22				 	0x36		// MAX7300 P22 register only




#endif /* I2C_H_ */
