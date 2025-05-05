#ifndef _LCD_H    
#define _LCD_H
#include <stdbool.h>

void i2cOut(unsigned char j);
void i2cStart(void);
void i2cStop(void);
void lcdInit(void);
void lcdNewLine(void);
void lcdClear(void);
void lcdPrintf(const char *format, ...);
void lcdGoTo(uint8_t dest);
void lcdReturnHome(void);
void setSCL(bool value);
void setSDA(bool value);

#endif 
