/*
===============================================================================
 Name        : lpc1769.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

// registro di colck delle periferiche
#define PCLKSEL0 *(volatile unsigned long*) 0x400FC1A8

// registri PIN CONNECT BLOCK
#define PINSEL0 *(volatile unsigned long*) 0x4002C000
#define PINSEL1 *(volatile unsigned long*) 0x4002C004
#define PINSEL3 *(volatile unsigned long*) 0x4002C00C
#define PINSEL4 *(volatile unsigned long*) 0x4002C010

// registri del convertitore analogico-digitale (ADC)
#define AD0CR *(volatile unsigned long*) 0x40034000
#define AD0INTEN *(volatile unsigned long*) 0x4003400C
#define AD0DR1 *(volatile unsigned long*) 0x40034014
#define AD0DR2 *(volatile unsigned long*) 0x40034018
#define AD0DR3 *(volatile unsigned long*) 0x4003401C
#define AD0DR4 *(volatile unsigned long*) 0x40034020
#define AD0DR5 *(volatile unsigned long*) 0x40034024
#define AD0DR6 *(volatile unsigned long*) 0x40034028

// registri PWM
#define PWM1PCR *(volatile unsigned long*) 0x4001804C
#define PWM1MR0 *(volatile unsigned long*) 0x40018018
#define PWM1MR1 *(volatile unsigned long*) 0x4001801C
#define PWM1MR2 *(volatile unsigned long*) 0x40018020
#define PWM1MR3 *(volatile unsigned long*) 0x40018024
#define PWM1MR4 *(volatile unsigned long*) 0x40018040
#define PWM1MR5 *(volatile unsigned long*) 0x40018044
#define PWM1MR6 *(volatile unsigned long*) 0x40018048
#define PWM1TCR *(volatile unsigned long*) 0x40018004
#define PWM1MCR *(volatile unsigned long*) 0x40018014
#define PWM1LER *(volatile unsigned long*) 0x40018050

#define CORE_CLK 96000000		// frequenza di clock del processore ARM
#define RTI_CLK CORE_CLK/4				// Repetitive Timer clock frequency

// Repetitive Interrupt Timer Registers
#define RICOMPVAL *(volatile unsigned long*) 0x400B0000
#define RIMASK *(volatile unsigned long*) 0x400B0004
#define RICTRL *(volatile unsigned long*) 0x400B0008
#define RICOUNTER *(volatile unsigned long*) 0x400B000C

// NVIC peripherals interrupt
#define ISER0 *(volatile unsigned long*) 0xE000E100

// Power Control for Peripherals register
#define PCONP *(volatile unsigned long*) 0x400FC0C4


// valori estremi dutycycle per PWM e periodo base
//#define PWM_dc_MAX	2460		// espresso in microsecondi
//#define PWM_dc_MIN	575			// espresso in microsecondi

#define PWM_dc_MAX	2400		// espresso in microsecondi
#define PWM_dc_MIN	600		// espresso in microsecondi
#define PWM_period 20000		// espresso in microsecondi

#define MAX_POINT_NUM	10
#define DELAY	2				// ritardo tra punti in secondi

#define ADC_avg	100

// punto della traiettoria
typedef struct point {
	unsigned int X1 : 16;		// impulso servomotore #1
	unsigned int X2 : 16;		// impulso servomotore #2
	unsigned int X3 : 16;		// impulso servomotore #3
	unsigned int X4 : 16;		// impulso servomotore #4
	unsigned int X5 : 16;		// impulso servomotore #5
	unsigned int X6 : 16;		// impulso servomotore #6

} point;

point sequence[MAX_POINT_NUM] = {
		{600, 600, 600, 600, 600, 600},		// punto #1
		{800, 800, 800, 800, 800, 800},		// punto #2
		{1000, 1000,1000,1000,1000,1000}, 	// punto #3
		{1200, 1200,1200,1200,1200,1200},	// punto #4
		{1400, 1400,1400,1400,1400,1400},	// punto #5
		{1600, 1600,1600,1600,1600,1600},	// punto #6
		{1800, 1800,1800,1800,1800,1800},	// punto #7
		{2000, 2000,2000,2000,2000,2000},	// punto #8
		{2200, 2200,2200,2200,2200,2200},	// punto #9
		{2400, 2400,2400,2400,2400,2400}	// punto #10

	};	// sequenza di punti


// valori letti dal convertitore analogico-digitale
unsigned int ADCvalue1, ADCvalue2, ADCvalue3, ADCvalue4, ADCvalue5, ADCvalue6;

/*
void RIT_IRQHandler(void)
{
	static int pointCnt = 0;

	PWM1MR1 = PWM1MR0/PWM_period*sequence[pointCnt].X1;	// carica in MR1 la durata del punto corrente
	PWM1MR2 = PWM1MR0/PWM_period*sequence[pointCnt].X2;	// carica in MR2 la durata del punto corrente
	PWM1MR3 = PWM1MR0/PWM_period*sequence[pointCnt].X3;	// carica in MR3 la durata del punto corrente
	PWM1MR4 = PWM1MR0/PWM_period*sequence[pointCnt].X4;	// carica in MR4 la durata del punto corrente
	PWM1MR5 = PWM1MR0/PWM_period*sequence[pointCnt].X5;	// carica in MR5 la durata del punto corrente
	PWM1MR6 = PWM1MR0/PWM_period*sequence[pointCnt].X6;	// carica in MR6 la durata del punto corrente

	PWM1LER |= 0b1111110;					// carica il valori preparato per MR1, MR2, MR3, MR4, MR5, MR6

	pointCnt++;
	if(pointCnt>=MAX_POINT_NUM)
		pointCnt=0;

	RICTRL |= 0b0001;					// Set RITINT in RICTRL register in order to clear the int flag
}
*/

void ADC_IRQHandler(void)
{
	ADCvalue1 = (ADCvalue1*(ADC_avg-1) + ((AD0DR1&0xFFFF)>>4))/ADC_avg;	// il risultato di conversione in AD0DR1 è contenuto nei bit 15:4
	ADCvalue2 = (ADCvalue2*(ADC_avg-1) + ((AD0DR2&0xFFFF)>>4))/ADC_avg;	// il risultato di conversione in AD0DR2 è contenuto nei bit 15:4
	ADCvalue3 = (ADCvalue3*(ADC_avg-1) + ((AD0DR3&0xFFFF)>>4))/ADC_avg;	// il risultato di conversione in AD0DR3 è contenuto nei bit 15:4
	ADCvalue4 = (ADCvalue4*(ADC_avg-1) + ((AD0DR4&0xFFFF)>>4))/ADC_avg;	// il risultato di conversione in AD0DR4 è contenuto nei bit 15:4
	ADCvalue5 = (ADCvalue5*(ADC_avg-1) + ((AD0DR5&0xFFFF)>>4))/ADC_avg;	// il risultato di conversione in AD0DR5 è contenuto nei bit 15:4
	ADCvalue6 = (ADCvalue6*(ADC_avg-1) + ((AD0DR6&0xFFFF)>>4))/ADC_avg;	// il risultato di conversione in AD0DR6 è contenuto nei bit 15:4

	PWM1MR1 = PWM1MR0/PWM_period*(ADCvalue1*(PWM_dc_MAX-PWM_dc_MIN)/4095+PWM_dc_MIN);
	PWM1MR2 = PWM1MR0/PWM_period*(ADCvalue2*(PWM_dc_MAX-PWM_dc_MIN)/4095+PWM_dc_MIN);
	PWM1MR3 = PWM1MR0/PWM_period*(ADCvalue3*(PWM_dc_MAX-PWM_dc_MIN)/4095+PWM_dc_MIN);
	PWM1MR4 = PWM1MR0/PWM_period*(ADCvalue4*(PWM_dc_MAX-PWM_dc_MIN)/4095+PWM_dc_MIN);
	PWM1MR5 = PWM1MR0/PWM_period*(ADCvalue5*(PWM_dc_MAX-PWM_dc_MIN)/4095+PWM_dc_MIN);
	PWM1MR6 = PWM1MR0/PWM_period*(ADCvalue6*(PWM_dc_MAX-PWM_dc_MIN)/4095+PWM_dc_MIN);

	PWM1LER |= 0b1111110;					// carica il valori preparato per MR1, MR2, MR3, MR4, MR5, MR6
}


int main(void) {

	// impostazioni convertitore analogico-digitale (ADC)
	PCONP |= 1<<12;									// attiva l'alimentazione del convertitore analogico-digitale
	AD0CR |= 0x21FF7E;								// bit PDN=1, bit BURST=1, bits CLKDIV valore massimo (255), bits SEL=7E (canali da 1 a 6)
	AD0INTEN |= 0b100000000;						// abilita l'interrupt globale per fine conversione
	PINSEL1 |= 0b0101010000000000000000;			// imposta la funzione di AD0.1, AD0.2, AD0.3 su P0.24, P0.25, P0.26
	PINSEL3 |= 0b11110000000000000000000000000000;	// imposta la funzione di AD0.4, AD0.5 su P1.30, P1.31
	PINSEL0 |= 0b10000000;							// imposta la funzione di AD0.6 su P0.3
	ISER0 |= 1<<22;									// attiva la ricezione interrupt da ADC su NVIC
	// ****************************************************************************************************************

	ADCvalue1 = ADCvalue2 = ADCvalue3 = ADCvalue4 = ADCvalue5 = ADCvalue6 = 0;

	// Repetitive Interrupt Timer settings
	//PCONP |= 1<<16;						// enables Repetitive Interrupt Timer power/clock
	//RICTRL |= 0b10;						// Set RITENCLR bit in RICTRL register
    //ISER0 |= 1<<29;						// enables in NVIC interrupt reception from RTI
    //RICOMPVAL = DELAY*RTI_CLK;			// imposta il ritardo in secondi

	// impostazioni PWM
	PINSEL4 |= 0b010101010101;		// collega i pin P2.0->P2.5 alle uscite PWM 1.1->PWM1.6
	PWM1PCR |= 0b111111000000000;	// abilita le uscite da PWM1 a PWM6
	PWM1MR0 = (CORE_CLK/4)/50;		// prepara per MR0 il valore per un periodo pari a 20ms (specifiche servomotore)
	PWM1MR1 = PWM1MR2 = PWM1MR3 = PWM1MR4 = PWM1MR5 = PWM1MR6 = PWM1MR0/PWM_period*PWM_dc_MIN;	// prepara per MRx un duty cycle min (posizione inizio rotazione)
	PWM1LER |= 0b1111111;		// carica i valori preparati per MR0, MR1, MR2, MR3, MR4, MR5, MR6
	PWM1MCR |= 0b10;			// PWMMR0R=1 imposta MR0 affinchè il conteggio del periodo riparta automaticamente
	PWM1TCR = 0b1001;			// NOTA BENE: da eseguire DOPO tutte le altre impostazioni. PWM Enable + Counter Enable
	// ****************************************************************************************************************

    // Enter an infinite loop, just waiting for interrupt
    while(1) {
    	__asm volatile ("wfi");		// Wait for interrupt
    }
    return 0 ;
}
