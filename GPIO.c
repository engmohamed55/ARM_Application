/*
 * DIO.c
 *
 *  Created on: 2/10/2019
 *      Author: Mina
 */
#include "GPIO.h"
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
void GPIO_Init(void)
{
    /********************************************************************************************
     *                                                                                          *
     * 1- Enable the clock to the port by setting the appropriate bits in the RCGCGPIO register *
     *                                                                                          *
     ********************************************************************************************/
    Set_Bit( SYSCTL_RCGCGPIO_R , 5 );
    Set_Bit( SYSCTL_RCGCGPIO_R , 4 );
    Set_Bit( SYSCTL_RCGCGPIO_R , 3 );
    Set_Bit( SYSCTL_RCGCGPIO_R , 2 );
    Set_Bit( SYSCTL_RCGCGPIO_R , 1 );
    Set_Bit( SYSCTL_RCGCGPIO_R , 0 );

    /********************************************************************************************
     *                                                                                          *
     * 2-Unlock all registers before doing any thing in any port's register                     *
     *                                                                                          *
     ********************************************************************************************/
    GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTC_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;


    /********************************************************************************************
     *                                                                                          *
     * 3-Enable writing on GPIOAFSEL, GPIOPUR, GPIOPDR, or GPIODEN registers                    *
     *                                                                                          *
     ********************************************************************************************/
    GPIO_PORTA_CR_R = 0x000000FF;
    GPIO_PORTB_CR_R = 0x000000FF;
    GPIO_PORTC_CR_R = 0x000000F0;
    GPIO_PORTD_CR_R = 0x000000FF;
    GPIO_PORTE_CR_R = 0x0000003F;
    GPIO_PORTF_CR_R = 0x0000001F;

    /********************************************************************************************************************
     *
     * 4- Disable alternative functions, The associated pin functions as a GPIO and is controlled by the GPIO registers.
     *
     ********************************************************************************************************************/
    GPIO_PORTA_AFSEL_R &=~ ( 0x000000FF );
    GPIO_PORTB_AFSEL_R &=~ ( 0x000000FF );
    GPIO_PORTC_AFSEL_R &=~ ( 0x000000F0 );
    GPIO_PORTD_AFSEL_R &=~ ( 0x000000FF );
    GPIO_PORTE_AFSEL_R &=~ ( 0x0000003F );
    GPIO_PORTF_AFSEL_R &=~ ( 0x0000001F );

    /********************************************************************************************************************
     *
     * 5- Enable digital function on all pins
     *
     ********************************************************************************************************************/
    //    GPIO_PORTA_PCTL_R &=~ ( 0x000000FF );
    //    GPIO_PORTB_PCTL_R &=~ ( 0x000000FF );
    //    GPIO_PORTC_PCTL_R &=~ ( 0x000000F0 );
    //    GPIO_PORTD_PCTL_R &=~ ( 0x000000FF );
    //    GPIO_PORTE_PCTL_R &=~ ( 0x0000003F );
    //    GPIO_PORTF_PCTL_R &=~ ( 0x0000001F );

    /********************************************************************************************************************
     *
     * 6- Disable analog function for all ports
     *
     ********************************************************************************************************************/
    GPIO_PORTA_AMSEL_R &=~ ( 0x000000FF );
    GPIO_PORTB_AMSEL_R &=~ ( 0x000000FF );
    GPIO_PORTC_AMSEL_R &=~ ( 0x000000F0 );
    GPIO_PORTD_AMSEL_R &=~ ( 0x000000FF );
    GPIO_PORTE_AMSEL_R &=~ ( 0x0000003F );
    GPIO_PORTF_AMSEL_R &=~ ( 0x0000001F );

    /********************************************************************************************
     *
     * 7- Set all pins as input as an initial state
     *
     ********************************************************************************************/
    GPIO_PORTA_DIR_R &=~ ( 0x000000FF ) ;
    GPIO_PORTB_DIR_R &=~ ( 0x000000FF ) ;
    GPIO_PORTC_DIR_R &=~ ( 0x000000F0 ) ;
    GPIO_PORTD_DIR_R &=~ ( 0x000000FF ) ;
    GPIO_PORTE_DIR_R &=~ ( 0x0000003F ) ;
    GPIO_PORTF_DIR_R &=~ ( 0x0000001F ) ;

    /*******************************************************************************************
     *
     *  8-Set the drive strength for each of the pins through the GPIODR8 Registers.  (8mA)
     *
     *******************************************************************************************/
    GPIO_PORTA_DR8R_R = 0xFF;
    GPIO_PORTB_DR8R_R = 0xFF;
    GPIO_PORTC_DR8R_R = 0xF0;
    GPIO_PORTD_DR8R_R = 0xFF;
    GPIO_PORTE_DR8R_R = 0x3F;
    GPIO_PORTF_DR8R_R = 0x1F;
}


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
void GPIO_SetPinDirection(PORTS PortNumber_a, uint8 PinNumber_a, PIN_DIRECTION Direction_a )
{
    switch (PortNumber_a)
    {
    case PORTA:
        if( Direction_a == OUTPUT )
        {
            Set_Bit( GPIO_PORTA_DIR_R , PinNumber_a );
            Set_Bit( GPIO_PORTA_DEN_R , PinNumber_a );/*enable digital function*/
        }
        else if( Direction_a == INPUT )
        {
            Clear_Bit( GPIO_PORTA_DIR_R , PinNumber_a ) ;
            Set_Bit( GPIO_PORTA_PUR_R , PinNumber_a ); //enable pull up resistor
            Set_Bit( GPIO_PORTA_DEN_R , PinNumber_a );/*enable digital function*/
        }
        else
        {
            /* do nothing*/
        }
        break;
    case PORTB:
        if( Direction_a == OUTPUT )
        {
            Set_Bit( GPIO_PORTB_DIR_R , PinNumber_a );
            Set_Bit( GPIO_PORTB_DEN_R , PinNumber_a );/*enable digital function*/
        }
        else if( Direction_a == INPUT )
        {
            Clear_Bit( GPIO_PORTB_DIR_R , PinNumber_a );
            Set_Bit( GPIO_PORTB_PUR_R , PinNumber_a ); //enable pull up resistor
            Set_Bit( GPIO_PORTB_DEN_R , PinNumber_a );/*enable digital function*/
        }
        else
        {
            /* do nothing*/
        }
        break;
    case PORTC:
        if( Direction_a == OUTPUT )
        {
            Set_Bit( GPIO_PORTC_DIR_R , PinNumber_a );
            Set_Bit( GPIO_PORTC_DEN_R , PinNumber_a );/*enable digital function*/
        }
        else if( Direction_a == INPUT )
        {
            Clear_Bit( GPIO_PORTC_DIR_R , PinNumber_a );
            Set_Bit( GPIO_PORTC_PUR_R , PinNumber_a ); //enable pull up resistor
            Set_Bit( GPIO_PORTC_DEN_R , PinNumber_a );/*enable digital function*/
        }
        else
        {
            /* do nothing*/
        }
        break;
    case PORTD:
        if( Direction_a == OUTPUT )
        {
            Set_Bit( GPIO_PORTD_DIR_R , PinNumber_a) ;
            Set_Bit( GPIO_PORTD_DEN_R , PinNumber_a );/*enable digital function*/
        }
        else if( Direction_a == INPUT )
        {
            Clear_Bit( GPIO_PORTD_DIR_R , PinNumber_a) ;
            Set_Bit( GPIO_PORTD_PUR_R , PinNumber_a ); //enable pull up resistor
            Set_Bit( GPIO_PORTD_DEN_R , PinNumber_a );/*enable digital function*/
        }
        else
        {
            /* do nothing*/
        }
        break;
    case PORTE:
        if( Direction_a == OUTPUT )
        {
            Set_Bit( GPIO_PORTE_DIR_R , PinNumber_a) ;
            Set_Bit( GPIO_PORTE_DEN_R , PinNumber_a );/*enable digital function*/
        }
        else if( Direction_a == INPUT )
        {
            Clear_Bit( GPIO_PORTE_DIR_R , PinNumber_a) ;
            Set_Bit( GPIO_PORTE_PUR_R , PinNumber_a ); //enable pull up resistor
            Set_Bit( GPIO_PORTE_DEN_R , PinNumber_a );/*enable digital function*/
        }
        else
        {
            /* do nothing*/
        }
        break;
    case PORTF:
        if( Direction_a == OUTPUT )
        {
            Set_Bit( GPIO_PORTF_DIR_R , PinNumber_a) ;
            Set_Bit( GPIO_PORTF_DEN_R , PinNumber_a );/*enable digital function*/
        }
        else if( Direction_a == INPUT )
        {
            Clear_Bit( GPIO_PORTF_DIR_R , PinNumber_a) ;
            Set_Bit( GPIO_PORTF_PUR_R , PinNumber_a ); //enable pull up resistor
            Set_Bit( GPIO_PORTF_DEN_R , PinNumber_a );/*enable digital function*/
        }
        else
        {
            /* do nothing*/
        }
        break;
    }
}


/**************************************************************************
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
void GPIO_WritePin( PORTS PortNumber_a, uint8 PinNumber_a, PIN_VALUE Value_a )
{
    switch ( PortNumber_a )
    {
    case PORTA:
        if( Value_a == HIGH)
        {
            Set_Bit( GPIO_PORTA_DATA_R , PinNumber_a );
        }
        else if( Value_a == LOW )
        {
            Clear_Bit( GPIO_PORTA_DATA_R , PinNumber_a );
        }
        else
        {
            /*do nothing*/
        }
        break;
    case PORTB:
        if( Value_a == HIGH)
        {
            Set_Bit( GPIO_PORTB_DATA_R , PinNumber_a );
        }
        else if( Value_a == LOW )
        {
            Clear_Bit( GPIO_PORTB_DATA_R , PinNumber_a );
        }
        else
        {
            /*do nothing*/
        }
        break;
    case PORTC:
        if( Value_a == HIGH)
        {
            Set_Bit( GPIO_PORTC_DATA_R , PinNumber_a );
        }
        else if( Value_a == LOW )
        {
            Clear_Bit( GPIO_PORTC_DATA_R , PinNumber_a );
        }
        else
        {
            /*do nothing*/
        }
        break;
    case PORTD:
        if( Value_a == HIGH)
        {
            Set_Bit( GPIO_PORTD_DATA_R , PinNumber_a );
        }
        else if( Value_a == LOW )
        {
            Clear_Bit( GPIO_PORTD_DATA_R , PinNumber_a );
        }
        else
        {
            /*do nothing*/
        }
        break;
    case PORTE:
        if( Value_a == HIGH)
        {
            Set_Bit( GPIO_PORTE_DATA_R , PinNumber_a );
        }
        else if( Value_a == LOW )
        {
            Clear_Bit( GPIO_PORTE_DATA_R , PinNumber_a );
        }
        else
        {
            /*do nothing*/
        }
        break;
    case PORTF:
        if( Value_a == HIGH)
        {
            Set_Bit( GPIO_PORTF_DATA_R , PinNumber_a );
        }
        else if( Value_a == LOW )
        {
            Clear_Bit( GPIO_PORTF_DATA_R , PinNumber_a );
        }
        else
        {
            /*do nothing*/
        }
        break;
    }
}


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
uint8 GPIO_ReadPin( PORTS PortNumber_a, uint8 PinNumber_a )
{
    uint8 Ret_Val = 0;
    switch (PortNumber_a)
    {
    case PORTA:
        Ret_Val = Get_Bit( GPIO_PORTA_DATA_R , PinNumber_a);
        break;
    case PORTB:
        Ret_Val = Get_Bit( GPIO_PORTB_DATA_R , PinNumber_a);
        break;
    case PORTC:
        Ret_Val = Get_Bit( GPIO_PORTC_DATA_R , PinNumber_a);
        break;
    case PORTD:
        Ret_Val = Get_Bit( GPIO_PORTD_DATA_R , PinNumber_a);
        break;
    case PORTE:
        Ret_Val = Get_Bit( GPIO_PORTE_DATA_R , PinNumber_a);
        break;
    case PORTF:
        Ret_Val = Get_Bit( GPIO_PORTF_DATA_R , PinNumber_a);
        break;
    }
    return Ret_Val;
}







