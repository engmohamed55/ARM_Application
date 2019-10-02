/*
 * LCD.c
 *
 * Created: 02-10-2019
 * Author : Mohamed AbdElkader
 */ 

#include "GPIO.h"
#include "LCD.h"
//#include "stdlib.h"


void delay(void)
{
    uint8 i;
    for(i=0;i<250;i++);
}

void LCD_sendCommand(const uint8 Command)
{
#ifdef EIGHT_BIT_MODE
    GPIO_WritePin(CONTROL_PORT,RS,LOW);
    GPIO_WritePin(CONTROL_PORT,RW,LOW);
    delay();
    GPIO_WritePin(CONTROL_PORT,E,HIGH);
    delay();
    DATA_PORT = Command;
    delay();
    Clear_Bit(CONTROL_PORT,E);
    delay();


#elif defined FOUR_BIT_MODE
    GPIO_WritePin(CONTROL_PORT,RS,LOW);
    GPIO_WritePin(CONTROL_PORT,RW,LOW);
    delay();
    GPIO_WritePin(CONTROL_PORT,E,HIGH);
    delay();
#ifdef LOWER_BITS
    GPIO_PORTC_DATA_R = (GPIO_PORTC_DATA_R & 0xF0) | ((0xF0 & Command)>>4);
#elif defined HIGHER_BITS
    GPIO_PORTC_DATA_R = (GPIO_PORTC_DATA_R & 0x0F) | (0xF0 & Command);
#endif
    delay();
    GPIO_WritePin(CONTROL_PORT,E,LOW);
    delay();
    GPIO_WritePin(CONTROL_PORT,E,HIGH);
    delay();
#ifdef LOWER_BITS
    GPIO_PORTC_DATA_R = (GPIO_PORTC_DATA_R & 0xF0) | (0x0F & Command);
#elif defined HIGHER_BITS
    GPIO_PORTC_DATA_R = (GPIO_PORTC_DATA_R & 0x0F) | ((0x0F & Command)<<4);
#endif
    GPIO_WritePin(CONTROL_PORT,E,LOW);
    delay();

#endif
}

void LCD_Init(void)
{
#ifdef EIGHT_BIT_MODE
    GPIO_SetPinDirection(PORTC, PINC0, OUTPUT);
    GPIO_SetPinDirection(PORTC, PINC1, OUTPUT);
    GPIO_SetPinDirection(PORTC, PINC2, OUTPUT);
    GPIO_SetPinDirection(PORTC, PINC3, OUTPUT);
    GPIO_SetPinDirection(PORTC, PINC4, OUTPUT);
    GPIO_SetPinDirection(PORTC, PINC5, OUTPUT);
    GPIO_SetPinDirection(PORTC, PINC6, OUTPUT);
    GPIO_SetPinDirection(PORTC, PINC7, OUTPUT);
    GPIO_SetPinDirection(PORTA, RS, OUTPUT);
    GPIO_SetPinDirection(PORTA, RW, OUTPUT);
    GPIO_SetPinDirection(PORTA, E, OUTPUT);
    LCD_sendCommand(LCD_8_BIT_2_LINES_COMMAND);
    LCD_sendCommand(CURSOR_OFF);
    LCD_Clear();

#elif defined FOUR_BIT_MODE

#ifdef LOWER_BITS
    GPIO_SetPinDirection(PORTC, PINC4, OUTPUT);
    GPIO_SetPinDirection(PORTC, PINC5, OUTPUT);
    GPIO_SetPinDirection(PORTC, PINC6, OUTPUT);
    GPIO_SetPinDirection(PORTC, PINC7, OUTPUT);
    GPIO_SetPinDirection(PORTA, RS, OUTPUT);
    GPIO_SetPinDirection(PORTA, RW, OUTPUT);
    GPIO_SetPinDirection(PORTA, E, OUTPUT);
    LCD_sendCommand(LCD_4_BIT_MODE);
    LCD_sendCommand(LCD_4_BIT_2_LINES_COMMAND);
    LCD_sendCommand(CURSOR_OFF);
    LCD_Clear();

#elif defined HIGHER_BITS
    GPIO_SetPinDirection(PORTC, PINC4, OUTPUT);
    GPIO_SetPinDirection(PORTC, PINC5, OUTPUT);
    GPIO_SetPinDirection(PORTC, PINC6, OUTPUT);
    GPIO_SetPinDirection(PORTC, PINC7, OUTPUT);
    GPIO_SetPinDirection(PORTA, RS, OUTPUT);
    GPIO_SetPinDirection(PORTA, RW, OUTPUT);
    GPIO_SetPinDirection(PORTA, E, OUTPUT);
    LCD_sendCommand(LCD_4_BIT_MODE);
    LCD_sendCommand(LCD_4_BIT_2_LINES_COMMAND);
    LCD_sendCommand(CURSOR_OFF);
    LCD_Clear();

#endif

#endif
}

void LCD_sendChar(const char Char)
{
#ifdef EIGHT_BIT_MODE
    GPIO_WritePin(CONTROL_PORT,RS,HIGH);
    GPIO_WritePin(CONTROL_PORT,RW,LOW);
    delay();
    GPIO_WritePin(CONTROL_PORT,E,HIGH);
    delay();
    DATA_PORT = Char;
    delay();
    Clear_Bit(CONTROL_PORT,E);
    delay();


#elif defined FOUR_BIT_MODE
    GPIO_WritePin(CONTROL_PORT,RS,HIGH);
    GPIO_WritePin(CONTROL_PORT,RW,LOW);
    delay();
    GPIO_WritePin(CONTROL_PORT,E,HIGH);
    delay();
#ifdef LOWER_BITS
    GPIO_PORTC_DATA_R = (GPIO_PORTC_DATA_R & 0xF0) | ((0xF0 & Char) >> 4);
#elif defined HIGHER_BITS
    GPIO_PORTC_DATA_R = (GPIO_PORTC_DATA_R & 0x0F) | (0xF0 & Char);
#endif
    delay();
    GPIO_WritePin(CONTROL_PORT,E,LOW);
    delay();
    GPIO_WritePin(CONTROL_PORT,E,HIGH);
    delay();
#ifdef LOWER_BITS
    DATA_PORT = (DATA_PORT & 0xF0) | (0x0F & Char);
#elif defined HIGHER_BITS
    GPIO_PORTC_DATA_R = (GPIO_PORTC_DATA_R & 0x0F) | ((0x0F & Char) << 4);
#endif
    GPIO_WritePin(CONTROL_PORT,E,LOW);
    delay();

#endif

}


void LCD_sendString(const char *str)
{
    uint8 i =0;
    while(str[i]!= '\0')
    {
        LCD_sendChar(str[i]);
        i++;
    }
}


void LCD_Clear(void)
{
    LCD_sendCommand(LCD_CLEAR);
}

void LCD_goToRowColumn(uint8 row,uint8 col)
{

    uint8 Address;

    /* first of all calculate the required address */
    switch(row)
    {
    case 0:
        Address=col;
        break;
    case 1:
        Address=col+0x40;
        break;
    case 2:
        Address=col+0x10;
        break;
    case 3:
        Address=col+0x50;
        break;
    }
    /* to write to a specific address in the LCD
     * we need to apply the corresponding command 0b10000000+Address */
    LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const uint8 *Str)
{
    LCD_Clear();
    LCD_Clear();
    LCD_goToRowColumn(row,col);
    LCD_sendString(Str); /* display the string */
}


//void LCD_IntToStr(const uint16 data)
//{
//    uint8 buff[16]; /* String to hold the ascii result */
//    //itoa(data,buff,10); /* 10 for decimal */
//    LCD_sendString(buff);
//}
