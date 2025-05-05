/*
 * File:    delay.c
 * Author:  Alex Rozek
 * Edited:  2025-04-11
 * Description:
 * Adds delay functions, in milliseconds and microseconds.
 */
#include "delay.h"

void __delay_ms(uint32_t ms)
{
    uint32_t Start=_CP0_GET_COUNT();
    uint32_t Duration=TICK_PER_MS*ms;
    while((_CP0_GET_COUNT()-Start)<Duration);
}

void __delay_us(uint32_t us)
{
    uint32_t Start=_CP0_GET_COUNT();
    uint32_t Duration=TICK_PER_US*us;
    while((_CP0_GET_COUNT()-Start)<Duration);
}