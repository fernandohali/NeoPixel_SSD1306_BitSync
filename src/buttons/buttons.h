#ifndef BUTTONS_H
#define BUTTONS_H

#include "pico/stdlib.h"
#include "pico/types.h"
#include <stdint.h>

#define BUTTON_A 5
#define BUTTON_B 6

void init_buttons();
void gpio_irq_handler(uint gpio, uint32_t events);

#endif // BUTTONS_H