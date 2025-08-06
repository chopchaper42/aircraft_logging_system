#include <stdio.h>
#include <stdint.h>
#include "gpio.h"
#include "clk.h"
#include "usart.h"
#include "nanoprintf.h"
#include <string.h>


void delay(uint32_t count);
void process_message(const char *buffer, uint32_t size);
int main(void);

uint16_t PA4 = PIN('A', 4);
uint16_t PA7 = PIN('A', 7);

int main()
{
    uint16_t USART_TX = PIN('A', 9);
    uint16_t USART_RX = PIN('A', 10);

    // Enable clock on GPIOA
    rcc_ahb1_enable(GPIOAEN);
    rcc_apb2_enable(USART1EN);

    gpio_set_mode(PA4, GPIO_MODE_OUTPUT);
    gpio_set_mode(PA7, GPIO_MODE_INPUT);
    gpio_set_mode(USART_TX, GPIO_MODE_ALTERNATE);
    gpio_set_mode(USART_RX, GPIO_MODE_ALTERNATE);

    set_alternate_function(USART_TX, 0b0111);
    set_alternate_function(USART_RX, 0b0111);

    usart_init(WORD_8_BITS, STOP_BIT_1, BAUD_RATE_9600);

    usart_send("hello!\r\n", 9);

    uint8_t led_on = 0;

    uint8_t buffer[32];
    uint8_t *p = buffer;
    uint32_t count = 0;
    uint8_t data;

    uint32_t switch_counter = 0;
    uint32_t rx_counter = 0;

    while(1)
    {
        if (!usart_read_data_empty())
        {
            rx_counter++;
            usart_receive(&data);
            *p++ = data;
            count++; // TODO: change count to [p - buffer]

            if (data == '\n' || data == '\r')
            {
                char msg[32];
                strncpy(msg, buffer, count - 1);
                process_message(msg, count - 1);
                npf_pprintf(&npf_putchar_adapter, NULL, "Message: %s\r\n", buffer);
                count = 0;
                p = buffer;
            }
        }

        if (gpio_get(PA7) && switch_counter > 100000)
        {
            if (!led_on)
            {
                gpio_set(PA4, HIGH);
            }
            else
            {
                gpio_set(PA4, LOW);
            }

            led_on = ~led_on;
            npf_pprintf(&npf_putchar_adapter, NULL, "led_on: %d\r\n", led_on);

            switch_counter = 0;
        }
        
        switch_counter++;
    }
}

void process_message(const char *buffer, uint32_t size)
{
    if (!strncmp(buffer, "ON", size))
    {
        gpio_set(PA4, HIGH);
    }

    if (!strncmp(buffer, "OFF", size))
    {
        gpio_set(PA4, LOW);
    }
}

void delay(uint32_t count)
{
    while(count--);
}