#ifndef TIMER_H
#define TIMER_H

// #include "types.h"
#include <stdint.h>

void init_timer(uint32_t freq);
uint32_t get_uptime_ticks();

#endif
