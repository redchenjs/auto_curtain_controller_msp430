#include <msp430.h>
/*
 * uart.c
 *
 *  Created on: 2017年2月19日
 *      Author: redchenjs
 */
/*
 * ---------UART---------
 * PORT     TYPE    PIN
 * TXD      OUT     P1.2
 * RXD      IN      P1.1
 * ---------------------
 */
void uart_init(void)
{
//	P1SEL  = BIT1 + BIT2;
//	P1SEL2 = BIT1 + BIT2;
//
//	UCA0CTL1 |= UCSSEL_2;
//	UCA0BR0 = 140;
//	UCA0BR1 = 0;
//	UCA0MCTL = UCBRS2 + UCBRS0;
//	UCA0CTL1 &= ~UCSWRST;
//	IE2 |= UCA0RXIE;
}

//#pragma vector=USCIAB0TX_VECTOR
//__interrupt void uart_tx_isr(void)
//{
//  UCA0TXBUF = string1[i++];                 // TX next character
//
//  if (i == sizeof string1)                  // TX over?
//    IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
//}

//#pragma vector=USCIAB0RX_VECTOR
//__interrupt void uart_rx_isr(void)
//{
//	while (!(IFG2&UCA0TXIFG));
//
//	UCA0TXBUF = UCA0RXBUF;
//  string1[j++] = UCA0RXBUF;
//  if (j > sizeof string1 - 1)
//  {
//    i = 0;
//    j = 0;
//    IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
//    UCA0TXBUF = string1[i++];
//  }
//}
