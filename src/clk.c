#include "clk.h"

const static uint32_t rcc_ahb_scales[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };
const static uint32_t rcc_apbx_scales[] = { 1, 2, 4, 8, 16 };

// TODO: Keep the variables or get every time from registers?
static rcc_ahb_prescaler = 1;
static rcc_apb1_prescaler = 1;
static rcc_apb2_prescaler = 1;

// enable the HSI clock
// 0th bit of Control Register (RCC_CR)
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

}

void get_ahb_prescaler()
{
    return rcc_ahb_prescaler;
}

// set the APB1&2 prescalers
void set_apb1_prescaler(apb_prescaler_t prescaler)
{

}

void get_apb1_prescaler()
{
    return rcc_apb1_prescaler;
}

void set_apb2_prescaler(apb_prescaler_t prescaler)
{

}

void get_apb2_prescaler()
{
    return rcc_apb2_prescaler;
}