/*
 * DIO.h
 *
 *  Created on: ???/???/????
 *      Author: Mina
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "standard_types.h"
#include "function_macros.h"
#include "tm4c123gh6pm.h"


typedef enum{INPUT,OUTPUT}PIN_DIRECTION;
typedef enum{LOW,HIGH}PIN_VALUE;
typedef enum{PORTA,PORTB,PORTC,PORTD,PORTE,PORTF}PORTS;
typedef enum{PINA0,PINA1,PINA2,PINA3,PINA4,PINA5,PINA6,PINA7}PORTA_PINS;
typedef enum{PINB0,PINB1,PINB2,PINB3,PINB4,PINB5,PINB6,PINB7}PORTB_PINS;
typedef enum{PINC0,PINC1,PINC2,PINC3,PINC4,PINC5,PINC6,PINC7}PORTC_PINS;
typedef enum{PIND0,PIND1,PIND2,PIND3,PIND4,PIND5,PIND6,PIND7}PORTD_PINS;
typedef enum{PINE0,PINE1,PINE2,PINE3,PINE4,PINE5}PORTE_PINS;
typedef enum{PINF0,PINF1,PINF2,PINF3,PINF4}PORTF_PINS;
/********************************************************************************************************************************************
 * Function Name : GPIO_Init
 *
 * Description   : 1- Enable the clock to the port by setting the appropriate bits in the RCGCGPIO register.
 *                 2-Unlock all registers before doing any thing in any port's register.
 *                 3-Enable writing on GPIOAFSEL, GPIOPUR, GPIOPDR, or GPIODEN registers.
 *                 4- Disable alternative functions, The associated pin functions as a GPIO and is controlled by the GPIO registers.
 *                 5- Enable digital function on all pins.
 *                 6- Disable analog function for all ports.
 *                 7- Set all pins as input as an initial state.
 *                 8-Set the drive strength for each of the pins through the GPIODR8 Registers.  (8mA)
 *
 *
 * INPUTS        : PortNumber_a , PinNumber_a , Value_a
 *
 * OUTPUTS       : void
 *
 * Return        : void
 *********************************************************************************************************************************************/
void GPIO_Init(void);

/**************************************************************************
 * Function Name : GPIO_SetPinDirection
 *
 * Description   : set direction of pin eather input or output
 *
 * INPUTS        : PortNumber_a , PinNumber_a , Value_a
 *
 * OUTPUTS       : void
 *
 * Return        : void
 **************************************************************************/
void GPIO_SetPinDirection(PORTS PortNumber_a, uint8 PinNumber_a, PIN_DIRECTION Direction_a );

/**************************************************************************1
 * Function Name : GPIO_WritePin
 *
 * Description   : Write a value on a certain pin
 *
 * INPUTS        : PortNumber_a , PinNumber_a , Value_a
 *
 * OUTPUTS       : void
 *
 * Return        : void
 **************************************************************************/
void GPIO_WritePin( PORTS PortNumber_a, uint8 PinNumber_a, PIN_VALUE Value_a );

/**************************************************************************
 * Function Name : GPIO_ReadPin
 *
 * Description   : read the input value on a pin
 *
 * INPUTS        : PortNumber_a , PinNumber_a
 *
 * OUTPUTS       : void
 *
 * Return        : Ret_Val
 **************************************************************************/
uint8 GPIO_ReadPin( PORTS PortNumber_a, uint8 PinNumber_a );

#endif /* GPIO_H_ */
