/****************************************
 *
 *  File Name: I2C.c        
 *                       
 *  Created on: Oct 1, 2019   
 * 
 *  Author: Stawro Walaa   
 *
 ****************************************/

#include "I2C.h"
void setRW(uint8_t mode) {

	if (mode == 0) {
		I2C1_MSA_R &= ~(1 << 0); /* Clear for transmitting */
	} else {
		I2C1_MSA_R |= (1 << 0); /* Set for receiving */
	}
}

void I2C_Init(void) {
	/*1. Enable the I2C clock using the RCGCI2C register in the System Control module (see page 348).*/
	SYSCTL_RCGCI2C_R |= SYSCTL_RCGCI2C_R1;

	/*2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register in the System
	 Control module (see page 340). To find out which GPIO port to enable, refer to Table
	 23-5 on page 1351.*/
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;

	/*	3. In the GPIO module, enable the appropriate pins for their alternate function using the
	 GPIOAFSEL register (see page 671). To determine which GPIOs to configure, see Table
	 23-4 on page 1344.*/
	GPIO_PORTA_AFSEL_R |= (1 << 6) | (1 << 7);
	GPIO_PORTA_DEN_R |= (1 << 6) | (1 << 7);

	/* 4. Enable the I2CSDA pin for open-drain operation. See page 676. */
	GPIO_PORTA_ODR_R |= (1 << 7);

	/*5. Configure the PMCn fields in the GPIOPCTL register to assign the I2C signals to the appropriate
	 pins. See page 688 and Table 23-5 on page 1351.*/
	GPIO_PORTA_PCTL_R |= ((3 << 28) | (3 << 24));

	/*6. Initialize the I2C Master by writing the I2CMCR register with a value of 0x0000.0010.*/
	I2C1_MCR_R |= (1 << 4);

	/*7. Set the desired SCL clock speed of 100 Kbps by writing the I2CMTPR register with the correct
	 value. The value written to the I2CMTPR register represents the number of system clock periods
	 in one SCL clock period. The TPR value is determined by the following equation:
	 TPR = (System Clock/(2*(SCL_LP + SCL_HP)*SCL_CLK))-1;
	 TPR = (16MHz/(2*(6+4)*100000))-1;
	 TPR = 7
	 Write the I2CMTPR register with the value of 0x0000.0009.*/
	I2C1_MTPR_R |= (7 << 0);

	/*8. Specify the slave address of the master  This sets the slave address to 0x3B.*/
	I2C1_MSA_R = (0x20 << 1);

	/*set the next operation is a Transmit by writing the I2CMSA register with a value of 0x0000.0076.*/
	setRW(0);

}

uint8_t I2C_sendRegAddress(uint8_t addressByte) {
	uint8_t errorCheck = 0;
	/*set the next operation is a Transmit by writing the I2CMSA register with a value of 0x0000.0076.*/
	setRW(0);

	/* Place data (byte) to be transmitted in the data register by writing the I2CMDR register with the
	 desired data.*/
	I2C1_MDR_R = addressByte;

	I2C1_MCS_R = (1 << 0) | (1 << 1); /*send START and RUN */

	while ((I2C1_MCS_R & (1 << 0)) != 0);

	/* Check error */
	if ((I2C1_MCS_R & (1 << 1)) != 0) {
		I2C1_MCS_R = (1 << 2); /* send stop bit */
		while ((I2C1_MCS_R & (1 << 0)) != 0);
		errorCheck = 1;
	}

	return errorCheck;
}
uint8_t I2C_sendByte(uint8_t dataByte) {
	uint8_t errorCheck = 0;
	/* condition is already write from send address */
	/*setRW(0);*/

	/* Place data (byte) to be transmitted in the data register by writing the I2CMDR register with the
	 desired data.*/
	I2C1_MDR_R = dataByte;

	I2C1_MCS_R = (1 << 0) | (1 << 2); /*send STOP and RUN */

	while ((I2C1_MCS_R & (1 << 0)) != 0);

	/* Check error */
	if ((I2C1_MCS_R & (1 << 1)) != 0) {
		I2C1_MCS_R = (1 << 2); /* send stop bit */
		while ((I2C1_MCS_R & (1 << 0)) != 0);
		errorCheck = 1;
	}

	return errorCheck;
}
uint8_t I2C_receiveByte(void) {
	uint8_t dataByte;
	/* set the next operation as read */
	setRW(1);

	I2C1_MCS_R = (1 << 0) | (1 << 2); /*send STOP and RUN */

	while ((I2C1_MCS_R & (1 << 0)) != 0);

	dataByte = I2C1_MDR_R;

	return dataByte;
}
