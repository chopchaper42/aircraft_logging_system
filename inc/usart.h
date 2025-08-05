#ifndef USART_H
#define USART_H

#include <stdint.h>
#include "clk.h"
#include <math.h>

#define USART_BASE ((volatile uint32_t *) 0x40011000)

#define USART_CR1_M (1U << 12)
#define USART_CR1_UE (1U << 13)
#define USART_CR1_OVER8 (1U << 15)
#define USART_CR1_TE (1U << 3)
#define USART_SR_TXE (1U << 7)
#define USART_SR_TC (1U << 6)

#define USART_DIV_FRACTION_COEFFICIEN 16

typedef enum
{
    WORD_8_BITS = 0b0,
    WORD_9_BITS = 0b1
} usart_word_length_t;

typedef enum
{
    STOP_BIT_1 = 0b00,
    STOP_BIT_HALF = 0b01,
    STOP_BIT_2 = 0b10,
    STOP_BIT_ONE_AND_HALF = 0b11
} usart_stop_bit_number_t;

typedef enum
{
    BAUD_RATE_4800 = 4800,
    BAUD_RATE_9600 = 9600,
    BAUD_RATE_115_200 = 115200
} usart_baud_rate_t;

struct usart
{
    volatile uint32_t USART_SR, USART_DR, USART_BRR, USART_CR1, USART_CR2, USART_CR3, USART_GTPR
};

void enable_usart();

// TODO: rewrite. Can eliminate the if-else part. Clear and set length instead
void usart_set_word_length(usart_word_length_t length);

void usart_set_stop_bits(usart_stop_bit_number_t stop_bits);

uint32_t usart_get_oversampling_bit();

void usart_set_baud_rate(usart_baud_rate_t baud_rate);

void usart_enable_transmition();

void usart_init(usart_word_length_t w_length, usart_stop_bit_number_t stop_bits, usart_baud_rate_t baud_rate);

void usart_send_char(char ch);

void usart_send(const char *data, uint32_t length);

#endif