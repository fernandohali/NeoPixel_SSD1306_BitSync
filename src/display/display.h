#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "../matriz_Numeros/matriz_Numeros.h"
// Definições do I2C
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

// Protótipos das funções
void init_display(ssd1306_t *ssd);

void interpretacao_do_caractere(ssd1306_t *ssd, char caractere);

void draw_content(ssd1306_t *ssd, char msg);
void draw_content_nunb(ssd1306_t *ssd, const char *msg);

#endif
