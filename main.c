/*
 * main.c
 *
 * Created: 02-10-2019
 * Author : Mohamed AbdElkader
 */

#include "clock.h"
#include "tm4c123gh6pm.h"
#include "OS.h"
#include "LCD.h"
#include "GPIO.h"
#include "I2C.h"
#include "UART.h"
#include "PWM.h"

sint8 i=0,j=0,flag=0;

void Test_GPIO(void)
{
    GPIO_PORTF_DATA_R ^= 0x02;
}

void Test_LCD(void)
{
    LCD_displayStringRowColumn(i,j,"AbdElkader");
    LCD_sendCommand(0xC0);
    LCD_sendString("      Team");
    if(flag==0)
    {
        j++;
        if(j==7)
        {
            flag=1;
        }
    }
    if(flag==1)
    {
        j--;
        if(j==0)
        {
            flag=0;
        }
    }
}



int main(void)
{
    CLOCK_Init();
    OS_Init();
    GPIO_Init();
    LCD_Init();
    I2C_Init();
    UART0_Init();
    PWM_Init();

    GPIO_SetPinDirection(PORTF, 1, OUTPUT);     /*GPIO configuration*/


    LCD_Clear();    /*LCD Configuration*/
    LCD_sendString("    Project");
    LCD_sendCommand(0xC0);
    LCD_sendString("     TivaC");

    /*Test case for OS*/
//    Create_Task(Test_GPIO,SECOND_LVL_PRIORITY,1000,1000,0); /*1000 ms delay periodic task*/
    Create_Task(Test_LCD,HIGHST_PRIORITY,500,500,0);

    OS_Run();   /*Start OS*/

    return 0;
}

