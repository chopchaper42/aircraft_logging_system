#include <stdint.h>

#define USART_BASE ((volatile uint32_t *) 0x40011000)

#define USART_CR1_M (1U << 12)
#define USART_CR1_UE (1U << 13)

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

void set_baud_rate(usart_baud_rate_t baud_rate)
{
    // calculate and set the usartdiv here
}