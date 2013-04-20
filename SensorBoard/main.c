#include <stdio.h>
#include <p18f26k22.h>
#include <string.h>
#include "system.h"
#include "serial.h"
#include "ADC.h"

void InterruptLow(void);
void InterruptHigh(void);

#pragma code InterruptLowVector = 0x18
void InterruptLowVector(void){
	_asm
		goto InterruptLow
	_endasm
}

#pragma code
#pragma interruptlow InterruptLow
void InterruptLow(void){
}

#pragma code InterruptHighVector = 0x08
void InterruptHighVector(void){
	_asm
		goto InterruptHigh
	_endasm
}

#pragma code
#pragma interrupt InterruptHigh
void InterruptHigh(void){
}

void initOSC(void);
void enableGlobalInterrupts(void);
void disableGlobalInterrupts(void);

void main(void){
    disableGlobalInterrupts();
	initOSC();
	initSerialCom();

	enableGlobalInterrupts();
	while(1){
	}
	return;
}

void  initOSC(void){
	unsigned long i;
	OSCCON = 0x72;
	OSCTUNEbits.PLLEN = 1;
	for (i=0;i < 10000;i++){
		Nop();
	}
}

void enableGlobalInterrupts(void){
	RCONbits.IPEN = 1;
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
}

void disableGlobalInterrupts(void){
	RCONbits.IPEN = 0;
	INTCONbits.GIEH = 0;
	INTCONbits.GIEL = 0;
}