#include "led.h"
#include "pico/stdlib.h"
#include <stdio.h>

// Inicializa os LEDs
void init_led(void)
{
	gpio_init(LED_GREEN_PIN);
	gpio_init(LED_BLUE_PIN);

	gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
	gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);

	gpio_put(LED_GREEN_PIN, false);
	gpio_put(LED_BLUE_PIN, false);
}

// Alterna o estado do LED azul
void toggle_led_blue()
{
	gpio_put(LED_BLUE_PIN, !gpio_get(LED_BLUE_PIN)); // Alterna o estado do LED
}

// Alterna o estado do LED verde
void toggle_led_green()
{
	gpio_put(LED_GREEN_PIN, !gpio_get(LED_GREEN_PIN)); // Alterna o estado do LED
}