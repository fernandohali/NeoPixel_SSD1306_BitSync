#ifndef _LED_H
#define _LED_H

#include <stdbool.h>
#include "pico/stdlib.h"
#include "pico/types.h"
#include <stdint.h>

#define LED_GREEN_PIN 11
#define LED_BLUE_PIN 12

void init_led(void);
void toggle_led_blue();   // Adicionado para alternar o LED azul
void toggle_led_green();  // Adicionado para alternar o LED verde

#endif // _LED_H
