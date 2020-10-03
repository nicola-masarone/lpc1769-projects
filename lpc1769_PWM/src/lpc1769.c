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

// registri GPIO
#define IO0IntStatF *(volatile unsigned long*) 0x40028088
#define IO0IntClr *(volatile unsigned long*) 0x4002808C
#define IO0IntEnF *(volatile unsigned long*) 0x40028094

// registro di abilitazione interrupt periferiche su NVIC
#define ISER0 *(volatile unsigned long*) 0xE000E100

// registri PWM
#define PWM1PCR *(volatile unsigned long*) 0x4001804C

#define PWM1MR0 *(volatile unsigned long*) 0x40018018
#define PWM1MR1 *(volatile unsigned long*) 0x4001801C
#define PWM1MR2 *(volatile unsigned long*) 0x40018020
#define PWM1MR3 *(volatile unsigned long*) 0x40018024

#define PWM1TCR *(volatile unsigned long*) 0x40018004
#define PWM1MCR *(volatile unsigned long*) 0x40018014
#define PWM1LER *(volatile unsigned long*) 0x40018050

#define CORE_CLK 96000000					// frequenza di clock del processore ARM
#define PWM_PERIOD	(CORE_CLK/4)/50			// periodo PWM pari a 1/50 di secondo


// Gestore di interrupt dal timer da GPIO (condiviso con ExtINT3)
void EINT3_IRQHandler (void)
{
	if(IO0IntStatF&1<<7)						// interrupt proveniente da P0.7
	{
		static int PWM1_Level = 100;

		PWM1MR1 = PWM_PERIOD*PWM1_Level/100;	// prepara per MR1 un duty cycle del PWM1_Level%
		PWM1_Level-=10;							// decrementa il duty cycle del 10% per il prossimo click
		if(PWM1_Level<0)
			PWM1_Level=100;

		PWM1LER |= 0b0010;						// carica il valori preparato per MR1
		IO0IntClr |= 1<<7;						// cancella l'interrupt GPIO appena gestito
	}

	if(IO0IntStatF&1<<8)						// interrupt proveniente da P0.8
	{
		static int PWM2_Level = 100;

		PWM1MR2 = PWM_PERIOD*PWM2_Level/100;	// prepara per MR2 un duty cycle del PWM2_Level%
		PWM2_Level-=10;							// decrementa il duty cycle del 10% per il prossimo click
		if(PWM2_Level<0)
			PWM2_Level=100;

		PWM1LER |= 0b0100;						// carica il valori preparato per MR2
		IO0IntClr |= 1<<8;						// cancella l'interrupt GPIO appena gestito
	}

	if(IO0IntStatF&1<<9)						// interrupt proveniente da P0.9
	{
		static int PWM3_Level = 100;

		PWM1MR3 = PWM_PERIOD*PWM3_Level/100;	// prepara per MR3 un duty cycle del PWM3_Level%
		PWM3_Level-=10;							// decrementa il duty cycle del 10% per il prossimo click
		if(PWM3_Level<0)
			PWM3_Level=100;

		PWM1LER |= 0b1000;						// carica il valori preparato per MR3
		IO0IntClr |= 1<<9;						// cancella l'interrupt GPIO appena gestito
	}
}


int main(void) {

	// impostazioni PWM
	PINSEL4 |= 0b010101;		// collega ai pin P2.0, P2.1, P2.2 le uscite PWM 1.1, PWM 1.2, PWM 1.3
	PWM1PCR |= 0b111000000000;	// abilita l'uscita PWM1, PWM2, PWM3

	PWM1MR0 = PWM_PERIOD;		// prepara per MR0 il valore per il periodo desiderato
	PWM1MR1 = PWM_PERIOD*100/100;// prepara per MR1 un duty cycle del 100%
	PWM1MR2 = PWM_PERIOD*100/100;// prepara per MR2 un duty cycle del 100%
	PWM1MR3 = PWM_PERIOD*100/100;// prepara per MR3 un duty cycle del 100%

	PWM1LER |= 0b1111;			// carica i valori preparati per MR0, MR1, MR2 e MR3

	PWM1MCR |= 0b10;			// PWMMR0R=1 imposta MR0 affinchè il conteggio del periodo riparta automaticamente

	PWM1TCR = 0b1001;			// NOTA BENE: da eseguire DOPO tutte le altre impostazioni. PWM Enable + Counter Enable
	// ****************************************************************************************************************

    // Impostazioni GPIO P0.9, P0.8, P0.7 input con pull-up (default al Reset) e abilitazione interrupt
    IO0IntEnF |= (0b111<<7);// abilita trasmissione interrupt da GPIO su fronte di discesa di P0.9, P0.8, P0.7
    ISER0 |= 1<<21;			// abilita in NVIC ricezione interrupt da GPIO


    // Enter an infinite loop, just waiting for interrupt
    while(1) {
    	__asm volatile ("wfi");		// Wait for interrupt
    }
    return 0 ;
}
