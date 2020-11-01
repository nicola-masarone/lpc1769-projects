/*
===============================================================================
 Name        : lpc1769.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

// registri PIN CONNECT BLOCK
#define PINSEL4 *(volatile unsigned long*) 0x4002C010

// registri System Tick Timer
#define STCTRL *(volatile unsigned long*) 0xE000E010
#define STRELOAD *(volatile unsigned long*) 0xE000E014
// massimo valore caricabile nel SysTick Timer (minima frequenza di lavoro)
#define SYSTICK_MAX_VAL 0xFFFFFF


// registri PWM
#define PWM1PCR *(volatile unsigned long*) 0x4001804C
#define PWM1MR0 *(volatile unsigned long*) 0x40018018
#define PWM1MR2 *(volatile unsigned long*) 0x40018020
#define PWM1TCR *(volatile unsigned long*) 0x40018004
#define PWM1MCR *(volatile unsigned long*) 0x40018014
#define PWM1LER *(volatile unsigned long*) 0x40018050

#define CORE_CLK 96000000		// frequenza di clock del processore ARM
#define MAX_FREQUENCY 988		// frequenza massima pari a 988Hz
#define MIN_FREQUENCY 262		// frequenza minima pari a 262Hz
#define VOLUME 80				// percentuale duty-cycle corrispondente al volume al contrario (100 spento, 0 al massimo)

// Gestore di interrupt dal timer di sistema
void SysTick_Handler(void)
{
	static int frequency=MIN_FREQUENCY;

	if(frequency>MAX_FREQUENCY)
		frequency=MIN_FREQUENCY;
	PWM1MR0 = (CORE_CLK/4)/frequency;		// prepara per MR0 il valore per il periodo desiderato
	PWM1MR2 = PWM1MR0*VOLUME/100;			// prepara per MR2 un duty cycle pari a VOLUME
	frequency++;							// prepara il prossimo valore di frequenza

	PWM1LER |= 0b0101;						// carica il valori preparato per MR0 e MR2
}


int main(void) {

    // Impostazioni System Tick Timer
    STRELOAD = SYSTICK_MAX_VAL/64;	// Carica il contatore per la frequenza minima possibile
    STCTRL = 7;						// Abilita il Timer, il suo interrupt, con clock interno

	// impostazioni PWM
	PINSEL4 |= 0b0100;			// collega al pin P2.1, l'uscita PWM 1.2 (per problemi su PWM 1.1 della mia scheda :-( )
	PWM1PCR |= 0b10000000000;	// abilita l'uscita PWM2
	PWM1MR0 = (CORE_CLK/4)/MIN_FREQUENCY;	// prepara per MR0 il valore per il periodo desiderato
	PWM1MR2 = PWM1MR0*VOLUME/100;			// prepara per MR2 un duty cycle pari a VOLUME
	PWM1LER |= 0b101;			// carica i valori preparati per MR0 e MR2
	PWM1MCR |= 0b10;			// PWMMR0R=1 imposta MR0 affinchè il conteggio del periodo riparta automaticamente
	PWM1TCR = 0b1001;			// NOTA BENE: da eseguire DOPO tutte le altre impostazioni. PWM Enable + Counter Enable
	// ****************************************************************************************************************

    // Enter an infinite loop, just waiting for interrupt
    while(1) {
    	__asm volatile ("wfi");		// Wait for interrupt
    }
    return 0 ;
}
