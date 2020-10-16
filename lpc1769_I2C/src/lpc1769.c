/*
===============================================================================
 Name        : lpc1769.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "lpc1769.h"	// include file with LPC1769 declarations
#include "i2c.h"		// include file with I2C declarations

extern unsigned char I2Cbuffer[I2C_BUFFER_LEN];		// I2C data buffer
extern unsigned char* I2CbufferPtr;					// I2C buffer pointer
extern int I2CbufferCnt;							// I2C buffer counter
extern int I2CrptStartPos;							// I2C Repeated Start position

unsigned int delay;

int main(void) {

     setupI2C1();						// I2C1 initialization

/*
    // Setting up buffer to be transmitted onto I2C1
    I2Cbuffer[0] = ADDR_24LC64_W;		// 24LC64 IC address for write operation
    I2Cbuffer[1] = 0;					// 24LC64 Address High Byte
    I2Cbuffer[2] = 0;					// 24LC64 Address Low Byte
    I2Cbuffer[3] = 157;					// 24LC64 Byte value
    I2CbufferCnt = 4;					// Total buffer size: address + data
    startI2C1();						// start I2C1

    delay = 1000000;
    while(delay--);

    // Setting up buffer to be transmitted onto I2C1
    I2Cbuffer[0] = ADDR_24LC64_W;		// 24LC64 IC address for write operation
    I2Cbuffer[1] = 0;					// 24LC64 Address High Byte
    I2Cbuffer[2] = 0;					// 24LC64 Address Low Byte
    I2CrptStartPos = 2;					// repeated start at 'nth' position
    I2Cbuffer[3] = ADDR_24LC64_R;		// 24LC64 IC address for read operation
    I2Cbuffer[4] = 0;					// 24LC64 data byte
    I2CbufferCnt = 5;					// Total buffer size: address + data
    startI2C1();						// start I2C1
*/

    // Setting up buffer to be transmitted onto I2C1
    I2Cbuffer[0] = ADDR_MAX7300_W;		// MAX7300 IC address for write operation
    I2Cbuffer[1] = MAX7300_CFG_REG;		// MAX7300 configuration register
    I2Cbuffer[2] = 0b00000001;			// Transition Detection Control disabled, Normal Operation (no shutdown)
    I2CbufferCnt = 3;					// Total buffer size: address + data
    startI2C1();						// start I2C1

    delay = 5000000;
    while(delay--);

    // Setting up buffer to be transmitted onto I2C1
    I2Cbuffer[0] = ADDR_MAX7300_W;			// MAX7300 IC address for write operation
    I2Cbuffer[1] = MAX7300_P20_P23_CFG_REG;	// MAX7300 P20 to P23 configuration register
    I2Cbuffer[2] = 0b10011010;				// P23 input, P22 output, P21 input P20 input
    I2CbufferCnt = 3;						// Total buffer size: address + data
    startI2C1();							// start I2C1

    delay = 5000000;
    while(delay--);

    // Setting up buffer to be transmitted onto I2C1
    I2Cbuffer[0] = ADDR_MAX7300_W;			// MAX7300 IC address for write operation
    I2Cbuffer[1] = MAX7300_P22;				// MAX7300 P22 register only
    I2Cbuffer[2] = 1;						// P22 output high
    I2CbufferCnt = 3;						// Total buffer size: address + data
    startI2C1();							// start I2C1

    delay = 5000000;
    while(delay--);

    // Setting up buffer to be transmitted onto I2C1
    I2Cbuffer[0] = ADDR_MAX7300_W;			// MAX7300 IC address for write operation
    I2Cbuffer[1] = MAX7300_P22;				// MAX7300 P22 register only
    I2Cbuffer[2] = 0;						// P22 output low
    I2CbufferCnt = 3;						// Total buffer size: address + data
    startI2C1();							// start I2C1

    delay = 5000000;
    while(delay--);

    // Setting up buffer to be transmitted onto I2C1
    I2Cbuffer[0] = ADDR_MAX7300_W;			// MAX7300 IC address for write operation
    I2Cbuffer[1] = MAX7300_P22;				// MAX7300 P22 register only
    I2Cbuffer[2] = 1;						// P22 output high
    I2CbufferCnt = 3;						// Total buffer size: address + data
    startI2C1();							// start I2C1

    // Enter an infinite loop, just waiting for interrupt
    while(1) {
    	__asm volatile ("wfi");		// Wait for interrupt
    }
    return 0 ;
}
