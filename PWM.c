/*
 * PWM.c
 *
 *  Created on: Oct 2, 2019
 *      Author: stawr
 */

#include "PWM.h"


void PWM_Init(void){
    SYSCTL_RCGCPWM_R |= 2;       /* enable clock to PWM1 */
    SYSCTL_RCGCGPIO_R |= 0x20;   /* enable clock to PORTF */
    SYSCTL_RCC_R &= ~0x00100000; /* no pre-divide for PWM clock */

    /* Enable port PF3 for PWM1 M1PWM7 */
     GPIO_PORTF_AFSEL_R = 8;      /* PF3 uses alternate function */
     GPIO_PORTF_PCTL_R &= ~0x0000F000; /* make PF3 PWM output pin */
     GPIO_PORTF_PCTL_R |= 0x00005000;
     GPIO_PORTF_DEN_R |= 8;       /* pin digital */

     PWM1_3_CTL_R = 0;            /* stop counter */
     PWM1_3_GENB_R = 0x0000008C;  /* M1PWM7 output set when reload, */

     PWM1_3_LOAD_R = 16000;       /* set load value for 1kHz (16MHz/16000) */


}
void PWM_SetDuctyCycle(uint16_t dutyCycle){
    PWM1_3_CMPA_R = dutyCycle;       /* set duty cycle to min */
}
void PWM_Start(void){
    PWM1_3_CTL_R = 1;            /* start timer */
    PWM1_ENABLE_R = 0x80;        /* start PWM1 ch7 */
}
