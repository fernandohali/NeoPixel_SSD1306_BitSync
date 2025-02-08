#include <stdio.h>
#include "display.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "../inc/ssd1306.h"
#include "../inc/font.h"

// Instância do display
ssd1306_t ssd;

void init_display()
{
    // Inicializa a comunicação I2C
    i2c_init(I2C_PORT, 400000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    // Inicializa o display
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, I2C_PORT, I2C_PORT);
    ssd1306_send_config(&ssd);
    ssd1306_send_data(&ssd);

    // Limpar o display
    ssd1306_fill(&ssd, false); // Limpa o display
    ssd1306_send_data(&ssd);
}
