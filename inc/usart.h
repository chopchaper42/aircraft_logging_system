#include <stdint.h>
#include "clk.h"
#include <math.h>

#define USART_BASE ((volatile uint32_t *) 0x40011000)

#define USART_CR1_M (1U << 12)
#define USART_CR1_UE (1U << 13)
#define USART_CR1_OVER8 (1U << 15)

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
    STOP_BIT_1 = 0,
    STOP_BIT_2 = 1
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

void enable_usart()
{
    struct usart *usart = (struct usart *) USART_BASE;

    // Set the UE bit to 1 in the USART_CR1 register
    usart->USART_CR1 |= USART_CR1_UE;
    
}

// TODO: rewrite. Can eliminate the if-else part. Clear and set length instead
void set_word_length(usart_word_length_t length)
{
    struct usart *usart = (struct usart *) USART_BASE;

    // Set the M bit to 0 in the USART_CR1 register to set word size to 8 bits
    // Set the M to 1 for 9 bits
    if (length == WORD_8_BITS)
    {
        usart->USART_CR1 &= ~USART_CR1_M;
    }
    else if (length == WORD_9_BITS)
    {
        usart->USART_CR1 |= USART_CR1_M;
    }
}

void set_stop_bits(usart_stop_bit_number_t stop_bits)
{
    struct usart *usart = (struct usart *) USART_BASE;

    // Clears 12th and 13th bits
    usart->USART_CR2 &= ~(0b11 << 12);

    usart->USART_CR2 |= ((stop_bits & 0b11) << 12);
}

uint32_t get_oversampling_bit()
{
    struct usart *usart = (struct usart *) USART_BASE;

    return (usart->USART_CR1 & USART_CR1_OVER8) >> 15;
}

void set_baud_rate(usart_baud_rate_t baud_rate)
{
    struct usart *usart = (struct usart *) USART_BASE;

    uint32_t ahb_prescaler = get_ahb_prescaler();
    uint32_t apb2_prescaler = get_apb2_prescaler();
    uint32_t usart_oversampling_bit = get_oversampling_bit();

    uint32_t usart_clock_frequency = HSI_FREQUENCY / (ahb_prescaler * apb2_prescaler);

    // We scale the UART_DIV by 16 to shift it to the left by 4, allowing to avoid float arithmetics
    uint32_t divident = 16 * usart_clock_frequency;
    uint32_t divisor = (8 * (2 - usart_oversampling_bit) * baud_rate);
    
    // [(a + (b/2)) / 2] rounds the integer
    uint32_t usart_div_scaled = (divident + (divisor / 2)) / divisor;

    // Shift 4 bits to the right to get the mantissa
    uint32_t mantissa = usart_div_scaled >> 4;

    // Clear all except the last 4 bits to get the fraction
    uint32_t fraction = usart_div_scaled & 0xF;

    // When OVER8 = 1, the DIV_fraction[3] must be cleared
    if (usart_oversampling_bit == 0b1)    
    {
        // Leave the first 3 less significant bits and clear the 4th
        fraction &= 0b0111;
    }

    usart->USART_BRR = (mantissa << 4) | fraction;

}