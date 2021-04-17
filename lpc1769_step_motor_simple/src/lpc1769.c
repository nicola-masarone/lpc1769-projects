/*
===============================================================================
 Name        : lpc1769.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "step_times.h"

#define FIO2DIR0 *(volatile unsigned long*) 0x2009C040
#define FIO2MASK0 *(volatile unsigned long*) 0x2009C050
#define FIO2PIN0 *(volatile unsigned long*) 0x2009C054
#define FIO2SET0 *(volatile unsigned long*) 0x2009C058

#define CORE_CLK 96000000								// ARM processor clock frequency

// Timer0 Registers
#define T0IR *(volatile unsigned long*) 0x40004000
#define T0TCR *(volatile unsigned long*) 0x40004004
#define T0MCR *(volatile unsigned long*) 0x40004014
#define T0MR0 *(volatile unsigned long*) 0x40004018
#define PCLK_TIMER0 CORE_CLK/4							// Timer0 clock frequency

// NVIC peripherals interrupt
#define ISER0 *(volatile unsigned long*) 0xE000E100

#define WAVE_SEQ_LEN	4								// wave drive sequence length
#define FULL_SEQ_LEN	4								// full-step sequence length
#define HALF_SEQ_LEN	8								// half-step sequence length

int seq_len = 0;
int cur_state = 0;										// sequence current state
int cur_step = 0;
int total_steps = 0;
int acc_len, const_len, dec_len;						// actual speed profiles length

typedef enum {CW, CCW}cw_ccw_enum;						// motor rotation
typedef enum {WAVE, FULL, HALF}seq_type_enum;			// sequence type

// step sequence values                   bBaA     bBaA     bBaA     bBaA     bBaA     bBaA     bBaA     bBaA
unsigned char wave_seq[WAVE_SEQ_LEN] = {0b00010, 0b01000, 0b00100, 0b10000};										// sequenza wave drive
unsigned char full_seq[FULL_SEQ_LEN] = {0b01010, 0b01100, 0b10100, 0b10010};										// sequenza full-step
unsigned char half_seq[HALF_SEQ_LEN] = {0b00010, 0b01010, 0b01000, 0b01100, 0b00100, 0b10100, 0b10000, 0b10010};	// sequenza half-step
unsigned char* seq_ptr;

cw_ccw_enum cur_rot = CW;
seq_type_enum cur_seq = WAVE;

extern unsigned int acc_times[ACC_LEN];

void TIMER0_IRQHandler(void)
{
	FIO2PIN0 = seq_ptr[cur_state];							// set sequence step: A-A*-B-B*

	if(cur_rot==CW)											// clockwise rotation
	{
		cur_state++;										// increment current state
		if(cur_state>(seq_len-1))
			cur_state = 0;									// reset current state
	}
	else													// counterclockwise rotation
	{
		cur_state--;										// decrement current state
		if(cur_state<0)
			cur_state = seq_len-1;							// reset current state
	}

	// speed management
	if(cur_step<acc_len)									// acceleration
		T0MR0 = acc_times[cur_step];
	else
		if(cur_step>(acc_len+const_len))
			T0MR0 = acc_times[--dec_len];					// deceleration

	cur_step++;												// update step counter
	if(cur_step>total_steps)
	{
		T0TCR = 0b10;										// Disable and reset Timer0
		T0TCR = 0b00;										// Disable Timer0
		cur_step = 0;										// Reset current step
	}

    T0IR = 0b1;												// Reset int flag for match ch0
}

int run_steps(seq_type_enum type, cw_ccw_enum rot, unsigned int length)
{
	if(length>MAX_RUN_LEN)							// by now if run length is over MAX_RUN_LEN
		length=MAX_RUN_LEN;							// we clip it

	total_steps = length;

	if(length>=(ACC_LEN+DEC_LEN))					// we can complete acceleration and deceleration profiles
	{
		acc_len = ACC_LEN;							// actual acceleration length is equal to max acceleration length
		dec_len = DEC_LEN;							// actual deceleration length is equal to max deceleration length
		const_len = length - (acc_len+dec_len);		// remaining steps executed with constant speed
	}
	else
	{
		dec_len = acc_len = length/2;				// acceleration and deceleration have same length
		const_len = length - (acc_len+dec_len);		// if run length is odd there is a constant speed length too
	}

	// select proper stepper sequence
    switch(type)
    {
    	case WAVE:
    		seq_ptr = wave_seq;
    		seq_len = WAVE_SEQ_LEN;
    	break;
    	case FULL:
    		seq_ptr = full_seq;
    		seq_len = FULL_SEQ_LEN;
    	break;
    	case HALF:
    		seq_ptr = half_seq;
    		seq_len = HALF_SEQ_LEN;
    	break;
    	default:
    		seq_ptr = half_seq;
    		seq_len = HALF_SEQ_LEN;
    }

    T0TCR |= 1;													// Start Timer0

	return 0;
}


int main(void)
{
    // Output settings
	FIO2DIR0 |= 0b11110;				// Set GPIO from P2.1 to P2.4 as output: A, A*, B, B*
    FIO2MASK0 |= 0xE1;					// mask bit P2.0, P2.5, p2.6 e P2.7 to not modify them when writing P2.1-P2.4

    // Timer0 settings
    T0MCR = 0b11;						// Reset on MR0 with IRQ
 	ISER0 |= 0b10;						// enable interrupt from TIMER0 to NVIC
    T0MR0 = acc_times[0];	 			// slowest speed

    cur_seq = FULL;						// Select stepper mode
    cur_rot = CCW;						// Select motor rotation

    // Enter an infinite loop, launch a motor run then pause the MCU
    while(1)
    {
    	if(!(T0TCR&0b1))						// Timer0 is not running, i.e. motor is stopped
    	{
    	    if(cur_rot==CW)						// toggles rotation for next run
    	    	cur_rot=CCW;
    	    else
    	    	cur_rot=CW;

    	    run_steps(cur_seq, cur_rot, 2000);	// execute motor run
    	}
    	__asm volatile ("wfi");
    }

    return 0 ;
}
