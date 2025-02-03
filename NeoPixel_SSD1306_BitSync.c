#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"

// Definições do SPI
// Vamos usar SPI 0 e atribuí-lo aos seguintes pinos GPIO
// Os pinos podem ser alterados, veja a tabela de seleção de funções GPIO no datasheet para mais informações sobre atribuições de GPIO
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

// Definições do I2C
// Este exemplo usará I2C0 nos pinos GPIO8 (SDA) e GPIO9 (SCL) operando a 400KHz.
// Os pinos podem ser alterados, veja a tabela de seleção de funções GPIO no datasheet para mais informações sobre atribuições de GPIO
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

// Definições do UART
// Por padrão, a saída padrão (stdout) do UART é `uart0`, então vamos usar a segunda UART disponível
#define UART_ID uart1
#define BAUD_RATE 115200

// Usaremos os pinos 4 e 5 para o UART1
// Os pinos podem ser alterados, veja a tabela de seleção de funções GPIO no datasheet para mais informações sobre atribuições de GPIO
#define UART_TX_PIN 4
#define UART_RX_PIN 5

int main()
{
    stdio_init_all();

    // Inicialização do SPI. Este exemplo usará SPI a 1MHz.
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // O chip select (CS) é ativo em nível baixo, então inicializamos ele em nível alto
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
    // Para mais exemplos de uso do SPI, veja https://github.com/raspberrypi/pico-examples/tree/master/spi

    // Inicialização do I2C. Operando a 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    // Para mais exemplos de uso do I2C, veja https://github.com/raspberrypi/pico-examples/tree/master/i2c

    // Configuração do UART
    uart_init(UART_ID, BAUD_RATE);
    // Configuração dos pinos TX e RX usando a seleção de função no GPIO
    // Consulte o datasheet para mais informações sobre seleção de funções
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // Uso das funções UART para enviar dados
    // Em um sistema padrão, printf também enviará saída via UART padrão
    
    // Envia uma string, com conversão de CR/LF
    uart_puts(UART_ID, " Olá, UART!\n");
    
    // Para mais exemplos de uso do UART, veja https://github.com/raspberrypi/pico-examples/tree/master/uart

    while (true) {
        printf("Olá, mundo!\n");
        sleep_ms(1000);
    }
}
