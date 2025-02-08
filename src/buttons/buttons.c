#include "buttons.h"
#include "pico/stdlib.h"
#include <stdio.h>

// Definição de variáveis globais
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento
static volatile int indice = 0;         // Índice para controlar o número exibido

void init_buttons();                               // Declaração da função de inicialização dos botões
void gpio_irq_handler(uint gpio, uint32_t events); // Declaração da função de interrupção

// Inicializa os botões com interrupções
void init_buttons()
{
    // Configura os pinos dos botões como entrada
    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);

    gpio_set_dir(BUTTON_A, GPIO_IN); // Define o pino do botão A como entrada
    gpio_set_dir(BUTTON_B, GPIO_IN); // Define o pino do botão B como entrada

    gpio_pull_up(BUTTON_A); // Habilita o resistor de pull-up no botão A
    gpio_pull_up(BUTTON_B); // Habilita o resistor de pull-up no botão B

    // Configura interrupções para os botões
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
}

// Função de interrupção com debounce
void gpio_irq_handler(uint gpio, uint32_t events)
{
    uint32_t current_time = to_us_since_boot(get_absolute_time()); // Obtém o tempo atual

    // Debounce - Evita múltiplos acionamentos em curto período de tempo

    if (current_time - last_time > 200000) // Verifica se passaram 200 ms desde o último evento
    {
        last_time = current_time; // Atualiza o tempo do último evento

        if (gpio == BUTTON_A) // Verifica se o botão A foi pressionado
        {
            void set_led_color_green();
        }
        else if (gpio == BUTTON_B) // Verifica se o botão B foi pressionado
        {
            void set_led_color_blue();
        }
    }
}