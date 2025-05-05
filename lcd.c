/*
 * File:    lcd.c
 * Author:  Alex Rozek
 * Edited:  2025-04-11
 * Description:
 * Driver for LCD NHD-C0216CiZ-FSW-FBW-3V3 with ST7032i using GPIOs to simulate I2C using bit banging
 * 2x16 characters, Chip-on-Glass (COG)
 */

#include "delay.h"
#include "lcd.h"
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

const char SLAVE = 0x7C;
const char SEND_COMMAND = 0x00;
const char SEND_DATA = 0x40;
const char NEW_LINE = 0xC0;

#define SCL_WRITE LATAbits.LATA2      
#define SDA_WRITE LATAbits.LATA3

#define SDA_READ PORTAbits.RA3


void setSCL(bool value)
{
    SCL_WRITE = value;
    __delay_us(5);
}

void setSDA(bool value)
{
    SDA_WRITE = value;
    __delay_us(5);
}

// Initialization For ST7032i 
void lcdInit(void)
{
    TRISCbits.TRISC14 = 0;  // Set C14 output
    LATCbits.LATC14 = 1;    // Turn on Enable pin   
    TRISCbits.TRISC13 = 0;  // Set C13 output
    LATCbits.LATC13 = 1;    // Turn On Back Light Circuit
    TRISAbits.TRISA2 = 0;   // Set CLK Pin to Output
    TRISAbits.TRISA3 = 0;   // Set SDA Pin to Output
    ODCAbits.ODCA2 = 1;     // Open Drain
    ODCAbits.ODCA3 = 1;     // Open Drain
    LATAbits.LATA2 = 1;     // Start High
    LATAbits.LATA3 = 1;     // Start High
    
    __delay_ms(50);         // Required for power-up
    
    i2cStart();
    i2cOut(SLAVE);
    i2cOut(SEND_COMMAND);  // Select Command Register
    i2cOut(0x38);          // 8 bit data, 2 lines, Instruction Table 0
    __delay_us(100);
    i2cOut(0x39);          // Switch to Instruction Table 1
    __delay_us(100);
    i2cOut(0x14);
    i2cOut(0x78);          // Contrast Set
    i2cOut(0x5D);          // Contrast set, booster on, Icon Display on
    i2cOut(0x6D);          // Follower circuit ratio
    i2cOut(0x0C);          // Turn Display on, Turn 
    i2cOut(0x01);          // Clear display, Return Cursor
    i2cOut(0x06);          // Increment, not shifting
    __delay_us(100);
    i2cStop();
}

//Sends a byte to ST7032i
void i2cOut(unsigned char j) 
{
    int n;
    unsigned char d;
    d=j;
    for(n=0;n<8;n++){
        if((d&0x80)==0x80)      //Test if bit is 1 or 0
        {
            setSDA(1);             
        }
        else
        {
            setSDA(0);
        }
        
        d=(d<<1);               //Shift Left
        setSCL(0);                 //Toggle Clock Pin
        setSCL(1);
        setSCL(0);
    }
    setSCL (1);                    
    while(SDA_READ == 1)     //Toggle Clock until ACK received
    {
        setSCL(0);
        setSCL(1);
    }
    setSCL(0);                     //Idle Clock state is low
    __delay_us(10);
}

//Creates Start Condition on SCL and SDA
void i2cStart(void)
{
    setSCL(1);
    setSDA(1);
    setSDA(0);
    setSCL(0);
}
//Creates Stop Condition on SCL and SDA
void i2cStop(void)
{
    setSDA(0);
    setSCL(0);
    setSCL(1);
    setSDA(1);
}

//Prints formatted string on LCD
void lcdPrintf(const char *format, ...)
{
	i2cStart();
	i2cOut(SLAVE);
	i2cOut(SEND_DATA);
   
    va_list args;
    va_start(args, format);
    char buffer[16];            // Adjust buffer size as needed
    int len = vsnprintf(buffer, sizeof(buffer), format, args);

    if (len > 0) 
    {
        for (int i = 0; i < len && buffer[i] != '\0'; i++) 
        {
            i2cOut(buffer[i]);
        }
    }
    va_end(args);
    
	i2cStop();
}

//Moves cursor to second line
void lcdNewLine(void)
{
	i2cStart();
	i2cOut(SLAVE);
	i2cOut(SEND_COMMAND);
	i2cOut(NEW_LINE);
	i2cStop();
}

//Clear LCD and return cursor to home
void lcdClear(void)
{
    i2cStart();
    i2cOut(SLAVE);
    i2cOut(SEND_COMMAND);
    i2cOut(0x38);
    __delay_us(10);
    i2cOut(0x39);      // Switch to Instruction table 1
    __delay_us(10);
    i2cOut(0x01);      // Clear display
    __delay_us(600);   // LCD Clear Requires ample delay
    i2cStop();
}

//Moves cursor to address
void lcdGoTo(uint8_t dest)
{
	i2cStart();
	i2cOut(SLAVE);
	i2cOut(SEND_COMMAND);
    if(dest < 0x7F)             //Avoid writing wrong value
    {
        i2cOut(dest | 0x80);    //Set DDRAM Address Counter Command, to dest
    }
	i2cStop();
}

//Returns cursor back to line 1, character 1
void lcdReturnHome(void)
{
    i2cStart();
	i2cOut(SLAVE);
	i2cOut(SEND_COMMAND);
	i2cOut(0x02);               //Return home
	i2cStop();
}