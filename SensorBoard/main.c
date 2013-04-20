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
	if(UART1_TX_INT_FLAG){
		uart1TxInterruptHandler();
	}
	
//	if(UART2_TX_INT_FLAG){
//		//uart2TxInterruptHandler();
//	}
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
	if(UART1_RX_INT_FLAG){
		uart1RxInterruptHandler();
	}

//	if(UART2_RX_INT_FLAG){
//		uart2RxInterruptHandler();
//	}
}

void initOSC(void);
void enableGlobalInterrupts(void);
void disableGlobalInterrupts(void);

void main(void){
	char byte = 0;
	char msg[] = "Hello UART!\r\n";
    disableGlobalInterrupts();
	initOSC();
	initSerialCom();
//	initADC();
	enableGlobalInterrupts();

	writeMsg(msg,strlen(msg),UART_CHANNEL1);
	
	while(1){

		if(rxHasData(UART_CHANNEL1)){
			byte = readByte(UART_CHANNEL1);
			writeByte(byte, UART_CHANNEL1);
		}

//		writeByte('C',UART_CHANNEL1);

//		TX1REG = 'A';
//		while(!TXSTA1bits.TRMT);
    }
	return;
}

void  initOSC(void){
	unsigned long i;
	OSCCON = 0x72;
	OSCTUNEbits.PLLEN = 1;
	for (i=0;i < 150000;i++){
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