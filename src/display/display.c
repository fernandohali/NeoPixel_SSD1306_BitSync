// display.c
#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/i2c.h"
#include "../inc/ssd1306.h"
#include "../inc/font.h"
#include "display.h"

void init_display(ssd1306_t *ssd)
{
    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA);                                        // Pull up the data line
    gpio_pull_up(I2C_SCL);                                        // Pull up the clock line
                                                                  // Inicializa a estrutura do display
    ssd1306_init(ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
    ssd1306_config(ssd);                                         // Configura o display
    ssd1306_send_data(ssd);                                      // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(ssd, false);
    ssd1306_send_data(ssd);
}

void draw_content(ssd1306_t *ssd, bool cor)
{
    printf("Desenhando conteúdo...\n");
    ssd1306_fill(ssd, !cor);
    ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor);
    ssd1306_draw_string(ssd, "CEPEDI   TIC37", 8, 10);
    ssd1306_draw_string(ssd, "EMBARCATECH", 20, 30);
    ssd1306_draw_string(ssd, "PROF WILTON", 15, 48);
    ssd1306_send_data(ssd);

    printf("Conteúdo desenhado. Aguardando 1 segundo...\n");
    sleep_ms(1000);
}
