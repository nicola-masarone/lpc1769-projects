/*
===============================================================================
 Name        : lpc1769.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#define FIO0DIR *(volatile unsigned long*) 0x2009C000
#define FIO0SET *(volatile unsigned long*) 0x2009C018
#define FIO0CLR *(volatile unsigned long*) 0x2009C01C

// Repetitive Interrupt Timer Registers
#define RICOMPVAL *(volatile unsigned long*) 0x400B0000
#define RIMASK *(volatile unsigned long*) 0x400B0004
#define RICTRL *(volatile unsigned long*) 0x400B0008
#define RICOUNTER *(volatile unsigned long*) 0x400B000C

// NVIC peripherals interrupt
#define ISER0 *(volatile unsigned long*) 0xE000E100

// Power Control for Peripherals register
#define PCONP *(volatile unsigned long*) 0x400FC0C4

#define PAUSE	__asm volatile ("wfi")	// Wait for interrupt

#define CORE_CLK 96000000				// ARM core clock frequency
#define RTI_CLK CORE_CLK/4				// Repetitive Timer clock frequency

#define YELLOW_A_ON		5				// YELLOW A ON duration
#define GREEN_A_ON		20				// GREEN A ON duration

#define YELLOW_B_ON		5				// YELLOW B ON duration
#define GREEN_B_ON		20				// GREEN B ON duration

#define YELLOW_P_ON		5				// YELLOW pedestrian ON duration
#define GREEN_P_ON		20				// GREEN pedestrian ON duration

typedef enum {RED_A, YELLOW_A, GREEN_A, RED_B, YELLOW_B, GREEN_B, RED_P, YELLOW_P, GREEN_P} semaphore_lamps;
typedef enum {ON, OFF} lamp_status;

void RIT_IRQHandler(void)
{
	RICTRL |= 0b0001;					// Set RITINT in RICTRL register in order to clear the int flag
}


void SetSemaphore(semaphore_lamps lamp, lamp_status status)
{
	switch(lamp)
	{
		case RED_A:
			if(status==ON)
				FIO0SET |= 1<<15;		// P0.15 J6-13
			else
				FIO0CLR |= 1<<15;		// P0.15 J6-13
		break;

		case YELLOW_A:
			if(status==ON)
				FIO0SET |= 1<<17;		// P0.17 J6-12
			else
				FIO0CLR |= 1<<17;		// P0.17 J6-12
		break;

		case GREEN_A:
			if(status==ON)
				FIO0SET |= 1<<18;		// P0.18 J6-11
			else
				FIO0CLR |= 1<<18;		// P0.18 J6-11
		break;

		case RED_B:
			if(status==ON)
				FIO0SET |= 1<<1;		// P0.1 J6-10
			else
				FIO0CLR |= 1<<1;		// P0.1 J6-10
		break;

		case YELLOW_B:
			if(status==ON)
				FIO0SET |= 1<<0;		// P0.0 J6-9
			else
				FIO0CLR |= 1<<0;		// P0.0 J6-9
		break;

		case GREEN_B:
			if(status==ON)
				FIO0SET |= 1<<6;		// P0.6 J6-8
			else
				FIO0CLR |= 1<<6;		// P0.6 J6-8
		break;

		case RED_P:
			if(status==ON)
				FIO0SET |= 1<<7;		// P0.7 J6-7
			else
				FIO0CLR |= 1<<7;		// P0.7 J6-7
		break;

		case YELLOW_P:
			if(status==ON)
				FIO0SET |= 1<<8;		// P0.8 J6-6
			else
				FIO0CLR |= 1<<8;		// P0.8 J6-6
		break;

		case GREEN_P:
			if(status==ON)
				FIO0SET |= 1<<9;		// P0.9 J6-5
			else
				FIO0CLR |= 1<<9;		// P0.9 J6-5
		break;

	}

}

int main(void) {

	// GPIO settings
	FIO0DIR |= 0b1101000001111000011;	// select output pins on P0 for semaphore lamps

	// Repetitive Interrupt Timer settings
	PCONP |= 1<<16;						// enables Repetitive Interrupt Timer power/clock
	RICTRL |= 0b10;						// Set RITENCLR bit in RICTRL register
    ISER0 |= 1<<29;						// enables in NVIC interrupt reception from RTI

    // Enter an infinite loop
    while(1)
    {
    	// In this interval driver B can go while driver A and pedestrian must stop
    	SetSemaphore(RED_A, ON);
    	SetSemaphore(GREEN_B, ON);
    	SetSemaphore(RED_B, OFF);
    	SetSemaphore(RED_P, ON);
    	SetSemaphore(YELLOW_P, OFF);
    	RICOMPVAL = GREEN_B_ON*RTI_CLK;
    	PAUSE;								// Wait for interrupt

    	SetSemaphore(GREEN_B, OFF);
    	SetSemaphore(YELLOW_B, ON);
    	RICOMPVAL = YELLOW_B_ON*RTI_CLK;
    	PAUSE;								// Wait for interrupt
    	//*********************************************************************************

    	// In this interval driver A can go while driver B and pedestrian must stop
    	SetSemaphore(RED_B, ON);
    	SetSemaphore(YELLOW_B, OFF);
    	SetSemaphore(GREEN_A, ON);
    	SetSemaphore(RED_A, OFF);
    	RICOMPVAL = GREEN_A_ON*RTI_CLK;
    	PAUSE;								// Wait for interrupt

    	SetSemaphore(GREEN_A, OFF);
    	SetSemaphore(YELLOW_A, ON);
    	RICOMPVAL = YELLOW_A_ON*RTI_CLK;
    	PAUSE;								// Wait for interrupt
    	//*********************************************************************************

    	// In this interval pedestrian can go while driver A and B must stop
    	SetSemaphore(RED_A, ON);
    	SetSemaphore(YELLOW_A, OFF);
    	SetSemaphore(GREEN_P, ON);
    	SetSemaphore(RED_P, OFF);
    	RICOMPVAL = GREEN_P_ON*RTI_CLK;
    	PAUSE;								// Wait for interrupt

    	SetSemaphore(GREEN_P, OFF);
    	SetSemaphore(YELLOW_P, ON);
    	RICOMPVAL = YELLOW_P_ON*RTI_CLK;
    	PAUSE;								// Wait for interrupt
    	//*********************************************************************************
    }
    return 0 ;
}
