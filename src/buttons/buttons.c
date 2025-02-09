#include "buttons.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../led/led.h"

#include "../inc/ssd1306.h"
#include "../display/display.h"

// Definição de variáveis globais
static volatile uint32_t last_time = 0;       // Armazena o tempo do último evento
static volatile bool led_green_state = false; // Estado do LED Verde
static volatile bool led_blue_state = false;  // Estado do LED Azul

extern ssd1306_t ssd; // Declaração externa do display

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
            led_green_state = !led_green_state;       // Alterna o estado do LED Verde
            gpio_put(LED_GREEN_PIN, led_green_state); // Atualiza o LED Verde

            /*
            Depois da leitura dos livres código limpo e arquitetura de software, acabei tendo uma nção de como o código funciona,
            também percebi que o código é bem organizado e de fácil entendimento, o que facilita a manutenção e a
            adição de novas funcionalidades.
            */

            // Atualiza o display
            char msg[32];
            /*
            Pensei em colocar a mensagem em português, mas tinha que fazer a quebra de linha depois das
            barras que estão ao redor do display.
            snprintf(msg, sizeof(msg), "LED Verde: %s", led_green_state ? "Ligado" : "Desligado");
            */

            snprintf(msg, sizeof(msg), "LED Verde: %s", led_green_state ? "ON" : "OFF");
            draw_content_nunb(&ssd, msg);

            // Envia mensagem para o Serial Monitor
            printf("Botão A pressionado. LED Verde: %s\n", led_green_state ? "Ligado" : "Desligado");
        }
        else if (gpio == BUTTON_B) // Verifica se o botão B foi pressionado
        {
            led_blue_state = !led_blue_state;       // Alterna o estado do LED Azul
            gpio_put(LED_BLUE_PIN, led_blue_state); // Atualiza o LED Azul

            // Atualiza o display
            char msg[32];

            // ? : Operador ternário é a mesma coisa do if
            snprintf(msg, sizeof(msg), "LED Azul: %s", led_blue_state ? "ON" : "OFF");
            draw_content_nunb(&ssd, msg);

            // Envia mensagem para o Serial Monitor
            printf("Botão B pressionado. LED Azul: %s\n", led_blue_state ? "Ligado" : "Desligado");
        }
    }
}