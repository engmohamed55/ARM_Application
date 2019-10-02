/****************************************
 *
 *  File Name: I2C.h        
 *                       
 *  Created on: Oct 1, 2019   
 * 
 *  Author: Stawro Walaa   
 *
 ****************************************/

#ifndef I2C_H_
#define I2C_H_

#include "tm4c123gh6pm.h"

void I2C_Init(void);
uint8_t I2C_sendRegAddress(uint8_t addressByte);
uint8_t I2C_sendByte(uint8_t dataByte);
uint8_t I2C_receiveByte(void);

#endif /* I2C_H_ */
