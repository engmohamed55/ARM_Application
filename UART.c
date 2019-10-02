/*
 * UART.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Nancy
 */

#include "tm4c123gh6pm.h"
#include "standard_types.h"


#define RX_BUFFER_MAX_SIZE 100

static uint16 RxBuffIndex=0;
static uint8 RxBuffer[RX_BUFFER_MAX_SIZE];


void UART0_Init(void)
{

    /* 1- Enable UART0 Module */
    SYSCTL_RCGCUART_R |=(1<<0);
    /* 2- Enable Clk of GPIO PortA */
    SYSCTL_RCGCGPIO_R |=(1<<0);
    /* 3- Set GPIO PortA Alternative function for bits A0=U0Rx, A1=U0Tx */
    GPIO_PORTA_AFSEL_R |=(1<<0) | (1<<1);
    /* 4- Configure PMC fields PCM value U0Tx==U0Rx=1 so at PORTA_PCTL PCM0( for A0)=1 and PORTA_PCTL PCM1( for A1)=1*/
    GPIO_PORTA_PCTL_R |=(1<<0) | (1<<4);
    /*5- Enable A0 and A1 as Digital Pins*/
    GPIO_PORTA_DEN_R |=(1<<0) | (1<<1);
    /* 6- Configure UART Frame */
    /* a) Disable UART0*/
    UART0_CTL_R &=~(1<<0);
    /* b) Set BaudRate Value=16000000/(16*9600)=104.16667*/
    /* Assign Integer part of BaudRate*/
    UART0_IBRD_R=104;
    /* Assign Fractional part of BaudRate = int(0.16667*64+0.5)=11*/
    UART0_FBRD_R=11;
    /* c) Set Size if Data in the Frame =8bit, no parity, bit 1 stop bit*/
    UART0_LCRH_R=(0x03<<5);
    /* d) Enable UART Clk to use system clk*/
    UART0_CC_R=0x00;
    /* e) Enable UART0 module, UART0 Transmit, UART0 Receive*/
    UART0_CTL_R =(1<<0) | (1<<8) | (1<<9);

    /* Enable UART0 interrupt */
    NVIC_EN0_R |=(1<<5);
    /* 7- Enable UART0 Interrupt Mask reg*/
    UART0_IM_R |=(1<<4);
}

void UART0_SendChar(uint8 CharMsg)
{
    while( (UART0_FR_R & 1<<5) !=0);
    UART0_DR_R=CharMsg;
}

void UART0_SendMsg(uint8 *Msg, uint8 len)
{
    uint8 i;
    for(i=0; i<len; i++)
    {
        UART0_SendChar(Msg[i]);
    }
}

uint8 UART0_Recievechar(void)
{
    while( (UART0_FR_R & 1<<4) !=0);
    return(UART0_DR_R);
}



void UART0_getReceivedMsg(uint8 Msg[], uint8* MsgLengthPtr)
{
    uint8 i;
    for (i = 0; i < RxBuffIndex; ++i)
    {
        Msg[i] = RxBuffer[i];
    }
    * MsgLengthPtr = RxBuffIndex;
    RxBuffIndex = 0;
}

void UART0_InterruptHandler(void)
{
    if(RxBuffIndex < RX_BUFFER_MAX_SIZE)
    {
        RxBuffer[RxBuffIndex++] = UART0_DR_R;
    }
    /* Clear UART0 interrupt Flag by writing 1 to bit RxF (bit 4)*/
    UART0_ICR_R |=(1<<4);
}





