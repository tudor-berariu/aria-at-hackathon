#ifndef SERIAL_H
#define SERIAL_H

#define UART1_TX_INT_FLAG PIR1bits.TX1IF
#define UART1_RX_INT_FLAG PIR1bits.RC1IF

#define UART2_TX_INT_FLAG PIR3bits.TX2IF
#define UART2_RX_INT_FLAG PIR3bits.RC2IF

#define UART1_TX_INT_ENABLE PIE1bits.TX1IE
#define UART1_RX_INT_ENABLE PIE1bits.RC1IE

#define UART2_TX_INT_ENABLE PIE3bits.TX2IE
#define UART2_RX_INT_ENABLE PIE3bits.RC2IE

#define UART1_TX_INT_PRIORITY IPR1bits.TX1IP
#define UART1_RX_INT_PRIORITY IPR1bits.RC1IP

#define UART2_TX_INT_PRIORITY IPR3bits.TX2IP
#define UART2_RX_INT_PRIORITY IPR3bits.RC2IP

#define CHANNEL1 0
#define CHANNEL2 1

int initSerialCom(void);

void uart1TxInterruptHandler(void);
void uart2TxInterruptHandler(void);
void uart1RxInterruptHandler(void);
void uart2RxInterruptHandler(void);
#endif
