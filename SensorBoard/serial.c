#include <p18f26k22.h>
#include <string.h>
#include "serial.h"

#define TX_BUF_LEN 32
#define RX_BUF_LEN 32

#define NUM_OF_CHANNELS 2

typedef struct SerialCom{
	struct{
		char buf[TX_BUF_LEN];	
		unsigned char head;
		unsigned char next;
	}tx;
	
	struct{
		char buf[RX_BUF_LEN];
		unsigned char head;
		unsigned char next;
		unsigned char overflow;
		unsigned buffull;
	}rx;
}SerialCom;

static SerialCom serialCom[NUM_OF_CHANNELS];

static void initUSART1(void);
static void initUSART2(void);
static int initSerialChannel(int channel);


static void initUSART1(void){
	TRISCbits.RC6 = 0;
	TRISCbits.RC7 = 1;
	ANSELCbits.ANSC6 = 0;
	ANSELCbits.ANSC7 = 0;
	BAUDCON1 = 0x08;
	SPBRG1 = 0x22;
	SPBRGH1 = 0x00;
	RCSTA1bits.CREN = 1;
	TXSTA1bits.SYNC = 0;
	RCSTA1bits.SPEN = 1;
	TXSTA1 |= 0x24;
	RCREG1 = 0;

	UART1_TX_INT_PRIORITY = 0;
	UART1_RX_INT_PRIORITY = 1;
	PIE1bits.RC1IE = 1;
	UART1_TX_INT_FLAG = 0;
	UART1_RX_INT_FLAG = 0;

	UART1_RX_INT_ENABLE = 1;
    UART1_TX_INT_ENABLE = 1;
	
}

static void initUSART2(void){
	Nop();
}

static int initSerialChannel(int channel){
	if((channel != CHANNEL1) && (channel != CHANNEL2)){
		return -1;
	}
	memset(serialCom[channel].tx.buf, 0, TX_BUF_LEN); 
	memset(serialCom[channel].rx.buf, 0, RX_BUF_LEN); 
	serialCom[channel].tx.head = 0;
	serialCom[channel].rx.head = 0;
	serialCom[channel].tx.next = 0;
	serialCom[channel].rx.next = 0;

	serialCom[channel].rx.overflow = 0;
	serialCom[channel].rx.buffull = 0;
	
	return 0;
}

int initSerialCom(void){
	if(initSerialChannel(CHANNEL1)){
		return -1;
	}
	if(initSerialChannel(CHANNEL2)){
		return -1;
	}
	initUSART1();
	initUSART2();
	return 0;
}

