#include <stdint.h>
#include "gpio.h"
#include "clk.h"
#include "usart.h"

void delay(uint32_t count);
int main(void);

int main()
{
    uint16_t PA4 = PIN('A', 4);
    uint16_t PA7 = PIN('A', 7);
    uint16_t USART_TX = PIN('A', 9);

    // Enable clock on GPIOA
    rcc_ahb1_enable(GPIOAEN);
    rcc_apb2_enable(USART1EN);

    gpio_set_mode(PA4, GPIO_MODE_OUTPUT);
    gpio_set_mode(PA7, GPIO_MODE_INPUT);
    gpio_set_mode(USART_TX, GPIO_MODE_ALTERNATE);

    set_alternate_function(USART_TX, 0b0111);

    usart_init(WORD_8_BITS, STOP_BIT_1, BAUD_RATE_9600);

    usart_send("hello!", 6);

    while(1)
    {
        gpio_set(PA4, HIGH);

        delay(500000);

        gpio_set(PA4, LOW);

        delay(500000);
    }
}

void delay(uint32_t count)
{
    while(count--);
}