#include "matriz_Numeros.h"
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

static inline void put_pixel(uint32_t pixel_grb);
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b);
void display_number(int buffer[5][5], uint8_t r, uint8_t g, uint8_t b);

// Variáveis globais para armazenar a cor (Entre 0 e 255 para intensidade)
uint8_t led_r = 255; // 25% de 255
uint8_t led_g = 0;
uint8_t led_b = 0;

// Definição da matriz de números
const int digits[10][NUM_PIXELS][5] = {
    // 0
    {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0}},
    // 1
    {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0}},
    // 2
    {
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 1, 1, 0}},
    // 3
    {
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0}},
    // 4
    {
        {0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0}},
    // 5
    {
        {0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0}},
    // 6
    {
        {0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0}},
    // 7
    {
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0}},
    // 8
    {
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0}},
    // 9
    {
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0}}};

// Função para enviar um pixel para a matriz de LEDs
static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

// Função para converter RGB para o formato GRB usado pelos LEDs
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

// Função para definir o padrão do número
void npSetPattern(char number)
{
    int num = number - '0'; // Converte o caractere para o número correspondente

      int r = led_r;
    int g = led_g;
    int b = led_b;

    int buffer[5][5]; // Definição correta da matriz temporária

    // Verifique os valores diretamente de digits[num]
    /*  printf("Matriz para o número %d:\n", num);
     for (int i = 0; i < 5; i++)
     {
         for (int j = 0; j < 5; j++)
         {
             printf("%d ", digits[num][i][j]);
         }
         printf("\n");
     }
  */
    // Agora preenche o buffer
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            buffer[i][j] = digits[num][4 - i][j];                     // Inverte as linhas ao copiar os dados
            /* printf("buffer[%d][%d]: %d\n", i, j, buffer[i][j]); */ // Imprime os valores do buffer
        }
    }

    display_number(buffer, r, g, b);
    sleep_ms(100);
}

void display_number(int buffer[5][5], uint8_t r, uint8_t g, uint8_t b)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (buffer[i][j])
            {
                put_pixel(urgb_u32(r, g, b));
            }
            else
            {
                put_pixel(0);
            }
        }
    }
}

// Limpa o buffer de pixels.
void limpar_matriz(void)
{
    for (uint i = 0; i < NUM_PIXELS; ++i)
        put_pixel(0); // Desliga todos os LEDs
}