#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"
#include "display/display.h"

int main()
{
    ssd1306_t ssd;      // Define o objeto ssd
    init_display(&ssd); // Passa o endereço de ssd com '&'

    bool cor = true;
    while (true)
    {
        cor = !cor;
        draw_content(&ssd, cor); // Passa o endereço de ssd com '&'
        sleep_ms(1000);
    }
}
