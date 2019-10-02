/*
 * PWM.h
 *
 *  Created on: Oct 2, 2019
 *      Author: stawr
 */

#ifndef PWM_H_
#define PWM_H_

#include "standard_types.h"
#include "tm4c123gh6pm.h"

void PWM_Init(void);
void PWM_SetDuctyCycle(uint16_t dutyCycle);
void PWM_Start(void);
#endif /* PWM_H_ */
