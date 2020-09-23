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

int main(void) {

        // Test: accensione/spegnimento LED integrato su scheda di sviluppo
    // da provare con breakpoint sulla prima istruzione ed esecuzione passo-passo
    FIO0DIR = 1<<22;
    FIO0SET = 1<<22;
    FIO0CLR = 1<<22;
    //*****************************************************************

    // Enter an infinite loop, pausing the MCU
    while(1) {
    	__asm volatile ("wfi");
    }
    return 0 ;
}
