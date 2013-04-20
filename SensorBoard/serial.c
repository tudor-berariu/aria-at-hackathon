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

void initUSART1(void);
static void initUSART2(void);
static int initSerialChannel(int channel);
static void enableUartRxInt(int channel);
static void disableUartRxInt(int channel);
static void enableUartTxInt(int channel);
static void disableUartTxInt(int channel);
static void clearOverflow(int channel);


void initUSART1(void){
	TRISCbits.RC6 = 0;
	TRISCbits.RC7 = 1;
	ANSELC = 0x00;
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
	TRISBbits.RB6 = 0;
	TRISBbits.RB7 = 1;
	ANSELB = 0x00;
	BAUDCON2 = 0x08;
	SPBRG2 = 0x22;
	SPBRGH2 = 0x00;
	RCSTA2bits.CREN = 1;
	TXSTA2bits.SYNC = 0;
	RCSTA2bits.SPEN = 1;
	TXSTA2 |= 0x24;
	RCREG2 = 0;

//	UART2_TX_INT_PRIORITY = 0;
//	UART2_RX_INT_PRIORITY = 1;
//	
//	UART2_TX_INT_FLAG = 0;
//	UART2_TX_INT_FLAG = 0;
//
//	UART2_RX_INT_ENABLE = 1;
//    UART2_TX_INT_ENABLE = 1;
}

static int initSerialChannel(int channel){
	if((channel != UART_CHANNEL1) && (channel != UART_CHANNEL2)){
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
	if(initSerialChannel(UART_CHANNEL1)){
		return -1;
	}
	if(initSerialChannel(UART_CHANNEL2)){
		return -1;
	}
	initUSART1();
	initUSART2();
	return 0;
}

int writeByte(char byte, int channel){
	if((channel != UART_CHANNEL1) && (channel != UART_CHANNEL2)){
		return -1;
	}
	
	disableUartTxInt(channel);
	if((serialCom[UART_CHANNEL1].tx.next+1)%(TX_BUF_LEN-1) == serialCom[UART_CHANNEL1].tx.head){
		enableUartTxInt(channel);
		return 0;
	}
	serialCom[channel].tx.buf[serialCom[channel].tx.next] = byte;
	serialCom[channel].tx.next = (serialCom[channel].tx.next+1)%(TX_BUF_LEN-1);
	
	enableUartTxInt(channel);
	return 1;		
}

int writeMsg(const char *msg, int len, int channel){
	unsigned int writeLen = 0;
	unsigned int count = 0;
	char byte = 0;
	char loopCondition = 0;
	
	if((channel != UART_CHANNEL1) && (channel != UART_CHANNEL2)){
		return -1;
	}
	writeLen = (len < TX_BUF_LEN )?len:TX_BUF_LEN;

	disableUartTxInt(channel);
	if((serialCom[UART_CHANNEL1].tx.next+1)%(TX_BUF_LEN-1) == serialCom[UART_CHANNEL1].tx.head){
		enableUartTxInt(channel);
		return 0;
	}

	do{
		disableUartTxInt(channel);
		serialCom[channel].tx.buf[serialCom[channel].tx.next] = *(msg+count);
		serialCom[channel].tx.next = (serialCom[channel].tx.next+1)%(TX_BUF_LEN-1);
		count++;
		loopCondition = ((serialCom[UART_CHANNEL1].tx.next+1)%(TX_BUF_LEN-1) != serialCom[UART_CHANNEL1].tx.head) && (count < writeLen);
		if((count%2) == 0){
			enableUartTxInt(channel);
		}
	}while(loopCondition);
	enableUartTxInt(channel);
	return count;
}



void uart1TxInterruptHandler(void){
	UART1_TX_INT_FLAG = 0;

	if(serialCom[UART_CHANNEL1].tx.head == serialCom[UART_CHANNEL1].tx.next){
		UART1_TX_INT_ENABLE = 0;
		return;
	}

	TXREG1 = serialCom[UART_CHANNEL1].tx.buf[serialCom[UART_CHANNEL1].tx.head];
	serialCom[UART_CHANNEL1].tx.head = (serialCom[UART_CHANNEL1].tx.head+1)%(TX_BUF_LEN-1);
}


char readByte(int channel){
	char byte;
	if((channel != UART_CHANNEL1) && (channel != UART_CHANNEL2)){
		return -1;
	}

	disableUartRxInt(channel);
	clearOverflow(channel);

	if(serialCom[channel].rx.head == serialCom[channel].rx.next){
		enableUartRxInt(channel);
		return 0;
	}

	byte = serialCom[channel].rx.buf[serialCom[channel].rx.head];
	serialCom[channel].rx.head = (serialCom[channel].rx.head+1)%(TX_BUF_LEN-1);
	enableUartRxInt(channel);

	return byte;
}

char rxHasData(int channel){
	char status = 0;

	if((channel != UART_CHANNEL1) && (channel != UART_CHANNEL2)){
		return -1;
	}

	disableUartTxInt(channel);
	if(serialCom[channel].rx.head != serialCom[channel].rx.next){
		status = 1;
	}
	enableUartRxInt(channel);
	return status;
}

void uart1RxInterruptHandler(void){

	do{
		if((serialCom[UART_CHANNEL1].rx.next+1)%(RX_BUF_LEN-1) != serialCom[UART_CHANNEL1].rx.head){
			serialCom[UART_CHANNEL1].rx.buf[serialCom[UART_CHANNEL1].rx.next] = RCREG1;
			serialCom[UART_CHANNEL1].rx.next = (serialCom[UART_CHANNEL1].rx.next+1)%(RX_BUF_LEN-1);	
		}else{
			serialCom[UART_CHANNEL1].rx.buffull = 1;
		}
		
	}while(UART1_RX_INT_FLAG != 0 && serialCom[UART_CHANNEL1].rx.buffull != 1);
	
	clearOverflow(UART_CHANNEL1);
}

void uart2TxInterruptHandler(void){
	UART2_TX_INT_FLAG = 0;

	if(serialCom[UART_CHANNEL2].tx.head == serialCom[UART_CHANNEL2].tx.next){
		UART2_TX_INT_ENABLE = 0;
		return;
	}

	TXREG2 = serialCom[UART_CHANNEL2].tx.buf[serialCom[UART_CHANNEL2].tx.head];
	serialCom[UART_CHANNEL2].tx.head = (serialCom[UART_CHANNEL2].tx.head+1)%(TX_BUF_LEN-1);
}

void uart2RxInterruptHandler(void){
	do{
		if((serialCom[UART_CHANNEL2].rx.next+1)%(RX_BUF_LEN-1) != serialCom[UART_CHANNEL2].rx.head){
			serialCom[UART_CHANNEL2].rx.buf[serialCom[UART_CHANNEL2].rx.next] = RCREG2;
			serialCom[UART_CHANNEL2].rx.next = (serialCom[UART_CHANNEL2].rx.next+1)%(RX_BUF_LEN-1);	
		}else{
			serialCom[UART_CHANNEL2].rx.buffull = 1;
		}
		
	}while(UART2_RX_INT_FLAG != 0 && serialCom[UART_CHANNEL2].rx.buffull != 1);
	
	clearOverflow(UART_CHANNEL2);
}

static void enableUartTxInt(int channel){
	if(channel == UART_CHANNEL1){
		UART1_TX_INT_ENABLE = 1;
	}else{
		UART2_TX_INT_ENABLE = 1;
	}
}

static void disableUartTxInt(int channel){
	if(channel == UART_CHANNEL1){
		UART1_TX_INT_ENABLE = 0;
	}else{
		UART2_TX_INT_ENABLE = 0;
	}	
}


static void enableUartRxInt(int channel){
	if(channel == UART_CHANNEL1){
		UART1_RX_INT_ENABLE = 1;
	}else{
		UART2_RX_INT_ENABLE = 1;
	}
}

static void disableUartRxInt(int channel){
	if(channel == UART_CHANNEL1){
		UART1_RX_INT_ENABLE = 0;
	}else{
		UART2_RX_INT_ENABLE = 0;
	}	
}

static void clearOverflow(int channel){
	if(channel == UART_CHANNEL1){
		if(RCSTA1bits.OERR){
			serialCom[channel].rx.overflow = 1;
			RCSTA1bits.CREN = 0;
			RCSTA1bits.CREN = 1;
		}
	}else{
		if(RCSTA2bits.OERR){
			serialCom[channel].rx.overflow = 1;
			RCSTA2bits.CREN = 0;
			RCSTA2bits.CREN = 1;
		}		
	}
}


