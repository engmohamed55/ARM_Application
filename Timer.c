/***************************************
 * Module: Timer Driver Source File
 *
 * Date: 1st October 2019
 *
 * Author: Mohamed AbdElkader
 */

#include "Timer.h"
#include "tm4c123gh6pm.h"



void OS_Long_Term(void);

void TIMER0_ISR(void)
{
    SET_BIT(REG(Timer0_16_32_base,GPTMICR),TATOCINT);
    OS_Long_Term();
}



void TIMER0_Init(void)
{

    /*Enable Module Clock*/
    SET_BIT(REG(RCGC1,RCGC1OFFSET),TIMER0);

    /*Disable the timer at first*/
    CLEAR_BIT(REG(Timer0_16_32_base,GPTMCTL),TAEN);

    /*32bit mode*/
    REG(Timer0_16_32_base,GPTMCFG)= 0x00000000;

    /*Periodic mode configuration*/
    REG(Timer0_16_32_base,GPTMTAMR) =  (REG(Timer0_16_32_base,GPTMTAMR) & PERIODIC) | (REG(Timer0_16_32_base,GPTMTAMR) & 0xFFFFFFFC);

    /*Count UP*/
    SET_BIT(REG(Timer0_16_32_base,GPTMTAMR),TACDIR);

    /*Loading Start Value*/
    REG(Timer0_16_32_base,GPTMTAILR) = 0x3E80;

    /*Enable Timer A Time-out Interrupt*/
    SET_BIT(REG(Timer0_16_32_base,GPTMIMR),TATOIM);

    /*Clear Time-out Flag Register*/
    SET_BIT(REG(Timer0_16_32_base,GPTMICR),TATOCINT);

    /*Enable Timer0 Interrupt*/
    EN0_INTERRUPT_ENABLE |= (1<<TIMER0_A_INT_NO);

    /*Enable the timer counting*/
    SET_BIT(REG(Timer0_16_32_base,GPTMCTL),TAEN);

}

void TIMER0_deInit(void)
{
    CLEAR_BIT(REG(RCGC1,RCGC1OFFSET),TIMER0);
}
