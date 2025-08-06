#include "usart.h"

void enable_usart()
{
    struct usart *usart = (struct usart *) USART_BASE;

    // Set the UE bit to 1 in the USART_CR1 register
    usart->USART_CR1 |= USART_CR1_UE;
    
}

// TODO: rewrite. Can eliminate the if-else part. Clear and set length instead
void usart_set_word_length(usart_word_length_t length)
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

void usart_set_stop_bits(usart_stop_bit_number_t stop_bits)
{
    struct usart *usart = (struct usart *) USART_BASE;

    // Clears 12th and 13th bits
    usart->USART_CR2 &= ~(0b11 << 12);

    usart->USART_CR2 |= ((stop_bits & 0b11) << 12);
}

uint32_t usart_get_oversampling_bit()
{
    struct usart *usart = (struct usart *) USART_BASE;

    return (usart->USART_CR1 & USART_CR1_OVER8) >> 15;
}

void usart_set_baud_rate(usart_baud_rate_t baud_rate)
{
    struct usart *usart = (struct usart *) USART_BASE;

    uint32_t ahb_prescaler = get_ahb_prescaler();
    uint32_t apb2_prescaler = get_apb2_prescaler();
    uint32_t usart_oversampling_bit = usart_get_oversampling_bit();

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

void usart_enable_transmition()
{
    struct usart *usart = (struct usart *) USART_BASE;

    // Set the TE (Transmition Enable) bit
    usart->USART_CR1 |= USART_CR1_TE;
}

void usart_enable_reception()
{
    struct usart *usart = (struct usart *) USART_BASE;

    // Set the RE (Reception Enable) bit
    usart->USART_CR1 |= USART_CR1_RE;
}

void usart_init(usart_word_length_t w_length, usart_stop_bit_number_t stop_bits, usart_baud_rate_t baud_rate)
{
    enable_usart();
    usart_set_word_length(w_length);
    usart_set_stop_bits(stop_bits);
    usart_set_baud_rate(baud_rate);
    usart_enable_transmition();
    usart_enable_reception();
}

void usart_send_char(char ch)
{
    struct usart *usart = (struct usart *) USART_BASE;

    while (!(usart->USART_SR & USART_SR_TXE));
    usart->USART_DR = ch;

    while (!(usart->USART_SR & USART_SR_TC));
}

void usart_send(const char *data, uint32_t length)
{
    struct usart *usart = (struct usart *) USART_BASE;

    for (uint32_t i = 0; i < length && data[i] != '\0'; i++)
    {
        while (!(usart->USART_SR & USART_SR_TXE));
        usart->USART_DR = data[i];
    }

    while (!(usart->USART_SR & USART_SR_TC));
}

void usart_receive(uint8_t *received_byte)
{
    struct usart *usart = (struct usart *) USART_BASE;

    *received_byte = usart->USART_DR;
}

uint8_t usart_read_data_empty()
{
    struct usart *usart = (struct usart *) USART_BASE;

    return (usart->USART_SR & USART_SR_RXNE) == 0;
}