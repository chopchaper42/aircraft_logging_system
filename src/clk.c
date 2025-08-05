#include "clk.h"

static const uint16_t ahb_prescaler_table[16] = {
    1, 1, 1, 1, 1, 1, 1, 1,   // 0xxx: SYSCLK not divided
    2, 4, 8, 16, 64, 128, 256, 512  // 1xxx: SYSCLK divided
};

static const uint16_t apbx_prescaler_table[8] = {
    1, 1, 1, 1,   // 0xx: SYSCLK not divided
    2, 4, 8, 16   // 1xx: SYSCLK divided
};

// enable the HSI clock
// 0th bit of Control Register (RCC_CR)
// Enebled by default after reset
void enable_hsi_rc()
{
    struct rcc *rcc = (struct rcc *) RCC_BASE;

    rcc->RCC_CR |= RCC_HSION;
}

// make HSI drive the system clock
void set_hsi_as_sysclk()
{
    struct rcc *rcc = (struct rcc *) RCC_BASE;

    rcc->RCC_CFGR &= ~(0b11);
}

// set the AHB prescaler
void set_ahb_prescaler(ahb_prescaler_t prescaler)
{
    struct rcc *rcc = (struct rcc *) RCC_BASE;

    // Clear bits 7:4
    rcc->RCC_CFGR &= ~(0b1111 << 4);

    // Set bits 7:4
    rcc->RCC_CFGR |= (prescaler << 4);
}

uint32_t get_ahb_prescaler()
{
    struct rcc *rcc = (struct rcc *) RCC_BASE;

    uint32_t ahb_prescaler = (rcc->RCC_CFGR >> 4) & 0b1111; // BETTER APPROACH

    return ahb_prescaler_table[ahb_prescaler];
}

// set the APB1&2 prescalers
// APB1 - bits 12:10
void set_apb1_prescaler(apb_prescaler_t prescaler)
{
    struct rcc *rcc = (struct rcc *) RCC_BASE;

    // Clear bits 12:10
    rcc->RCC_CFGR &= ~(0b111 << 10);

    // Set bits 12:10
    rcc->RCC_CFGR |= (prescaler << 10);
}

uint32_t get_apb1_prescaler()
{
    struct rcc *rcc = (struct rcc *) RCC_BASE;

    uint32_t apb1_prescaler = (rcc->RCC_CFGR >> 10) & 0b111;

    return apbx_prescaler_table[apb1_prescaler];
}

void set_apb2_prescaler(apb_prescaler_t prescaler)
{
    struct rcc *rcc = (struct rcc *) RCC_BASE;

    // Clear bits 15:13
    rcc->RCC_CFGR &= ~(0b111 << 13);

    // Set bits 15:13
    rcc->RCC_CFGR |= (prescaler << 13);
}

uint32_t get_apb2_prescaler()
{
    struct rcc *rcc = (struct rcc *) RCC_BASE;

    uint32_t apb2_prescaler = (rcc->RCC_CFGR >> 13) & 0b111;

    return apbx_prescaler_table[apb2_prescaler];
}

void rcc_ahb1_enable(rcc_ahb1_peripheral_bit_t bit)
{
    struct rcc *rcc = (struct rcc *) RCC_BASE;

    rcc->RCC_AHB1ENR |= (0b1 << bit);
}

void rcc_ahb1_disable(rcc_ahb1_peripheral_bit_t bit)
{
    struct rcc *rcc = (struct rcc *) RCC_BASE;

    rcc->RCC_AHB1ENR &= ~(0b1 << bit);
}

// Enable an APB2 peripheral
void rcc_apb2_enable(rcc_apb2_peripheral_bit_t bit)
{
    struct rcc *rcc = (struct rcc *) RCC_BASE;

    rcc->RCC_APB2ENR |= (0b1 << bit);
}

// Disable an APB2 peripheral
void rcc_apb2_disable(rcc_apb2_peripheral_bit_t bit)
{
    struct rcc *rcc = (struct rcc *) RCC_BASE;

    rcc->RCC_APB2ENR &= ~(0b1 << bit);
}
