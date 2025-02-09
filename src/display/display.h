// display.h
#ifndef _DISPLAY_H
#define _DISPLAY_H

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

// Protótipos das funções
void init_display(ssd1306_t *ssd);
void draw_content(ssd1306_t *ssd, bool cor);

#endif
