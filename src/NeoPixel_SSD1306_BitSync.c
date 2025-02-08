#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "ws2812.pio.h"
#include "led/led.h"
#include "buttons/buttons.h"
#include "matriz_Numeros/matriz_Numeros.h"
#include "display/display.h"
#include "inc/ssd1306.h"
#include "inc/font.h"

#define BAUD_RATE 115200

PIO pio = pio0;
int sm = 0;
uint offset;

// Variável global para o display SSD1306
// Sei que não prcisa disso só com apenas um função, mas queria colocar aqui.
ssd1306_t ssd;

int main()
{
    char valor;

    stdio_init_all();
    // Inicializa os LEDs e os botões
    init_led();
    init_buttons();

    // Incilizar o display
    init_display();

    /* // Inicializa a UART
    uart_init(uart0, BAUD_RATE);
    gpio_set_function(0, GPIO_FUNC_UART); // Configura o pino TX
    gpio_set_function(1, GPIO_FUNC_UART); // Configura o pino RX */

    // Inicializa a comunicação WS2812
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    // Inicializa o display SSD1306
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, 0x3C, i2c0);
    ssd1306_config(&ssd);
    ssd1306_fill(&ssd, false); // Limpa o display

    while (true)
    {
        // Verifica se há caracteres disponíveis para leitura
        if (uart_is_readable(uart0))
        {
            char c = uart_getc(uart0);

            // Exibe o caractere no display SSD1306
            ssd1306_fill(&ssd, false); // Limpa o display antes de exibir o novo caractere
            ssd1306_draw_char(&ssd, c, 0, 0);
            ssd1306_send_data(&ssd);

            // Verifica se o caractere é um número entre 0 e 9
            if (c >= '0' && c <= '9')
            {
                int number = c - '0'; // Converte o caractere para um número
                npSetPattern(number); // Exibe o símbolo correspondente na matriz WS2812
            }
        }

        // Aqui você pode adicionar a lógica para ler os botões
        // ...

        sleep_ms(100);
    }
}