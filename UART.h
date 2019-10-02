/*
 * UART.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Nancy
 */

#ifndef MCAL_UART_H_
#define MCAL_UART_H_

void UART0_Init(void);
void UART0_SendChar(uint8 CharMsg);
void UART0_SendMsg(uint8 *Msg, uint8 len);
uint8 UART0_Recievechar(void);
void UART0_getReceivedMsg(uint8 Msg[], uint8* MsgLengthPtr);
void UART0_Test(void);

#endif /* MCAL_UART_H_ */
