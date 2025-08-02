#include <stdint.h>

#define USART_BASE ((volatile uint32_t *) 0x40011000)

#define USART_CR1_M (1U << 12)
#define USART_CR1_UE (1U << 13)
#define USART_CR2_STOP (1U << 12)

typedef enum
{
    WORD_8_BITS = 0,
    WORD_9_BITS = 1
} usart_word_length_t;

typedef enum
{
    STOP_BIT_1 = 0x0,
    STOP_BIT_HALF = 0x1,
    STOP_BIT_2 = 0x2,
    STOP_BIT_ONE_AND_HALF = 0x3
} usart_stop_bit_number_t;

typedef enum
{
    STOP_BIT_1 = 0,
    STOP_BIT_2 = 1
} usart_stop_bit_number_t;

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

    if (stop_bits == STOP_BIT_1)
    {
        //usart->USART_CR2 |= 
    }
}