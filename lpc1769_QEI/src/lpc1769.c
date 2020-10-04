/*
===============================================================================
 Name        : lpc1769.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

// definizione registri QEI
#define FIO0DIR *(volatile unsigned long*) 0x2009C000
#define FIO0SET *(volatile unsigned long*) 0x2009C018
#define FIO0CLR *(volatile unsigned long*) 0x2009C01C

#define PCONP *(volatile unsigned long*) 0x400FC0C4
#define PINSEL3 *(volatile unsigned long*) 0x4002C00C

#define QEIPOS *(volatile unsigned long*) 0x400BC00C
#define QEIMAXPOS *(volatile unsigned long*) 0x400BC010
#define FILTER *(volatile unsigned long*) 0x400BC03C
#define QEICONF *(volatile unsigned long*) 0x400BC008

// definizione registri 7-segmenti
#define FIO2DIR *(volatile unsigned long*) 0x2009C040
#define FIO2SET *(volatile unsigned long*) 0x2009C058
#define FIO2CLR *(volatile unsigned long*) 0x2009C05C
#define FIO2PIN *(volatile unsigned long*) 0x2009C054

// registri System Tick Timer
#define STCTRL *(volatile unsigned long*) 0xE000E010
#define STRELOAD *(volatile unsigned long*) 0xE000E014

// frequenza di clock del processore ARM
#define CORE_CLK 96000000
// carica in SysTick Timer il valore di aggiornamento del 7-segmenti
#define SYSTICK_VAL CORE_CLK/100			// 1/100 di secondo


// definizioni bit 7-segmenti
// Nota bene: tutti i segnali di uscita sono attivi bassi
// quindi per accendere un LED bisogna impostare a livello logico basso l'output
// P2.0 Led A, P2.1 Led B, P2.2 Led C, P2.3 Led D, P2.4 Led E, P2.5 Led F, P2.6 Led G, P2.7 Led DP
//	P2.10 abilita Cifra 1, P2.11 abilita Cifra 2

// funzione di attivazione dei LED corrispondenti alla cifra desiderata
void setDigits(char digit)
{
	FIO2SET = 0xFF;			// spegne tutti i LED del 7 segmenti
	switch(digit)
	{
		case 0:
			FIO2CLR = 0x3F;	// LED A, B, C, D, E, F accesi
		break;
		case 1:
			FIO2CLR = 0x06;	// LED B, C accesi
		break;
		case 2:
			FIO2CLR = 0x5B;	// LED A, B, D, E, G accesi
		break;
		case 3:
			FIO2CLR = 0x4F;	// LED A, B, C, D, E, G accesi
		break;
		case 4:
			FIO2CLR = 0x66;	// LED B, C, F, G accesi
		break;
		case 5:
			FIO2CLR = 0x6D;	// LED A, C, D, F, G accesi
		break;
		case 6:
			FIO2CLR = 0x7D;	// LED A, C, D, E, F, G accesi
		break;
		case 7:
			FIO2CLR = 0x07;	// LED A, B, C accesi
		break;
		case 8:
			FIO2CLR = 0x7F;	// LED A, B, C, D, E, F, G accesi
		break;
		case 9:
			FIO2CLR = 0x6F;	// LED A, B, C, D, E, F accesi
		break;
		default:			// valore impossibile
			FIO2SET = 0xFF;	// tutto spento
	}
}

// Gestore di interrupt dal timer di sistema
// all'interno è realizzato sia l'incremento del numero a due cifre da visualizzare (ogni secondo)
// sia l'aggiornamento delle cifre che vengono accese in modo alternato (ogni centesimo di secondo)
void SysTick_Handler(void)
{
	//static unsigned long counter = 0;
	static int number = 0;
	int digit;

	number = QEIPOS/2;		// carica il valore del contatore encoder nella variabile number
							// lo switch rotativo fa contare 2 impulsi per ogni posizione fissa

	if(FIO2PIN & 0x0400)	// test sul pin P2.10 (cifra 1, più significativa)
	{
		// se entriamo qui vuol dire che la cifra 1 era spenta e la cifra 2 era accesa, quindi invertiamo
		FIO2SET = 0x0800;	// P2.11 alto => spegni cifra 2
		digit = number/10; 	// calcolo cifra più significativa
		if(digit==0)		// scrive solo cifre diverse da zero
			digit=-1;		// forza la cancellazione della cifra più significativa con un valore impossibile
		setDigits(digit);
		FIO2CLR = 0x0400;	// P2.10 basso => accendi cifra 1
	}
	else
	{
		// se entriamo qui vuol dire che la cifra 1 era accesa e la cifra 2 era spenta, quindi invertiamo
		FIO2SET = 0x0400;	// P2.10 alto => spegni cifra 1
		digit = number%10;	// calcolo cifra meno significativa
		setDigits(digit);
		FIO2CLR = 0x0800;	// P2.11 basso => accendi cifra 2
	}
}



int main(void) {

	// Impostazioni QEI (Quadrature Encoder Interface)
    PCONP |= 1<<18;					// PCQEI=1: attiva alimentazione QEI
    PINSEL3 = 0b010100000100000000;	// Funzione MCI0(PhA), MCI1(PhB), MCI2(Idx) sui pin P1.20, P1.23, P1.24
    QEIMAXPOS = 47;					// Massimo valore di conteggio per l'encoder (dopo il contatore si azzera)
    FILTER = (CORE_CLK/4)/1000;		// Imposta il filtro digitale di ritardo per evitare false commutazioni

	// Imposta GPIO da P2.0 a P2.7 e P2.10, P2.11 come output
    FIO2DIR |= 0x0CFF;

    // Imposta a livello logico alto tutti gli output (che sono in logica negata, quindi attivi bassi)
    FIO2SET = 0x0CFF;

	// Impostazioni System Tick Timer
	STRELOAD = SYSTICK_VAL;		// Carica il contatore per la frequenza di aggiornamento
	STCTRL = 7;					// Abilita il Timer, il suo interrupt, con clock interno


    // Enter an infinite loop, just waiting for interrupt
    while(1) {
    	__asm volatile ("wfi");		// Wait for interrupt
    }

    return 0 ;
}
