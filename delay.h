#ifndef _DELAY_H
#define _DELAY_H

#include <xc.h>
#define TICK_PER_MS (24000000/2/1000)
#define TICK_PER_US (24000000/2/1000/1000)

void __delay_us(uint32_t us);
void __delay_ms(uint32_t ms);

#endif
