#ifndef _MATRIZ_NUMEROS_H
#define _MATRIZ_NUMEROS_H

#define IS_RGBW false
#define NUM_PIXELS 25
#define WS2812_PIN 7

extern const int digits[10][NUM_PIXELS][5]; // Declaração da matriz de números

void npSetPattern(int number); // Função para definir o padrão do número
void limpar_matriz(void);

#endif
