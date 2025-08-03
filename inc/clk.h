#include <stdint.h>

#define HSI_FREQUENCY 16000000
#define LSI_FREQUENCY 32000

#define RCC_BASE 0x40023800

#define RCC_HSION 0b1

struct rcc
{
    volatile uint32_t RCC_CR, RCC_PLLCFGR, RCC_CFGR, RCC_CIR, RCC_AHB1RSTR,
                    RCC_AHB2RSTR, RCC_RESERVED0[2], RCC_APB1RSTR, RCC_APB2RSTR,
                    RCC_RESERVED1[2], RCC_AHB1ENR, RCC_AHB2ENR, RCC_RESERVED2[2],
                    RCC_APB1ENR, RCC_APB2ENR, RCC_RESERVED3[2], RCC_AHB1LPENR,
                    RCC_AHB2LPENR, RCC_RESERVED4[2], RCC_APB1LPENR, RCC_APB2LPENR,
                    RCC_RESERVED5[2], RCC_BDCR, RCC_CSR, RCC_RESERVED6[2],
                    RCC_SSCGR, RCC_PLLI2SCFGR, RCC_RESERVED7, RCC_DCKCFGR 
};

typedef enum
{
    AHB_PRESCALER_1 = 1,
    AHB_PRESCALER_2 = 2,
    AHB_PRESCALER_4 = 4,
    AHB_PRESCALER_8 = 8,
    AHB_PRESCALER_16 = 16,
    AHB_PRESCALER_32 = 32,
    AHB_PRESCALER_64 = 64,
    AHB_PRESCALER_128 = 128,
    AHB_PRESCALER_256 = 256,
    AHB_PRESCALER_512 = 512
} ahb_prescaler_t;

typedef enum
{
    APB_PRESCALER_1 = 1,
    APB_PRESCALER_2 = 2,
    APB_PRESCALER_4 = 4,
    APB_PRESCALER_8 = 8,
    APB_PRESCALER_16 = 16
} apb_prescaler_t;

// enable the HSI clock
// 0th bit of Control Register (RCC_CR)
void enable_hsi_rc();

// make HSI drive the system clock
void set_hsi_as_sysclk();

// set the AHB prescaler
void set_ahb_prescaler(ahb_prescaler_t prescaler);
void get_ahb_prescaler();

// set the APB1&2 prescalers
void set_apb1_prescaler(apb_prescaler_t prescaler);
void get_apb1_prescaler();

void set_apb2_prescaler(apb_prescaler_t prescaler);
void get_apb2_prescaler();