/*
 * File:    main.c
 * Author:  Alex Rozek
 * Edited:  2025-04-30
 * Description:
 * Demonstrates the lcd.c driver for the NHD-C0216CiZ-FSW-FBW-3V3 with ST7032i LCD Driver
 * Displays the following:
 * 
 * Countdown:  ##
 * To Launch     
 *
 * https://newhavendisplay.com/content/specs/NHD-C0216CiZ-FSW-FBW-3V3.pdf
 * 
 */
#include "config.h"
#include "delay.h"
#include "lcd.h"

int main() 
{
    lcdInit();

    while (1) 
    {
        lcdClear();
        lcdPrintf("Countdown:");
        lcdNewLine();
        lcdPrintf("To Launch");
        lcdReturnHome();
        

        for(int i = 100; i > 0; i--)    
        {
            lcdGoTo(11);
            lcdPrintf("%3d", i);        // Update countdown number every second
            __delay_ms(1000);
        }
        
    }
    return(1);
}




