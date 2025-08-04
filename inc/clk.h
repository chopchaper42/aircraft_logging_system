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
    AHB_PRESCALER_1 = 0b0001,
    AHB_PRESCALER_2 = 0b1000,
    AHB_PRESCALER_4 = 0b1001,
    AHB_PRESCALER_8 = 0b1010,
    AHB_PRESCALER_16 = 0b1011,
    AHB_PRESCALER_64 = 0b1100,
    AHB_PRESCALER_128 = 0b1101,
    AHB_PRESCALER_256 = 0b1110,
    AHB_PRESCALER_512 = 0b1111
} ahb_prescaler_t;

typedef enum
{
    APB_PRESCALER_1 = 0b001,
    APB_PRESCALER_2 = 0b100,
    APB_PRESCALER_4 = 0b101,
    APB_PRESCALER_8 = 0b110,
    APB_PRESCALER_16 = 0b111
} apb_prescaler_t;

typedef enum
{
    GPIOAEN = 0,
    GPIOBEN = 1,
    GPIOCEN = 2,
    GPIODEN = 3,
    GPIOEEN = 4,
    GPIOHEN = 7,
    CRCEN = 12,
    DMA1EN = 21,
    DMA2EN = 22
} rcc_ahb1_peripheral_bit_t;

typedef enum
{
    TIM1EN = 0,
    USART1EN = 4,
    USART6EN = 5,
    ADC1EN = 8,
    SDIOEN = 11,
    SPI1EN = 12,
    SPI4EN = 13,
    SYSCFGEN = 14,
    TIM9EN = 16,
    TIM10EN = 17,
    TIM11EN = 18,
    SPI5EN = 20
} rcc_apb2_peripheral_bit_t;

// enable the HSI clock
// 0th bit of Control Register (RCC_CR)
void enable_hsi_rc();

// make HSI drive the system clock
void set_hsi_as_sysclk();

// set the AHB prescaler
void set_ahb_prescaler(ahb_prescaler_t prescaler);
uint32_t get_ahb_prescaler();

// set the APB1&2 prescalers
void set_apb1_prescaler(apb_prescaler_t prescaler);
uint32_t get_apb1_prescaler();

void set_apb2_prescaler(apb_prescaler_t prescaler);
uint32_t get_apb2_prescaler();

// Enable an AHB1 peripheral
void rcc_ahb1_enable(rcc_ahb1_peripheral_bit_t bit);

// Disable an AHB1 peripheral
void rcc_ahb1_disable(rcc_ahb1_peripheral_bit_t bit);


// Enable an APB2 peripheral
void rcc_apb2_enable(rcc_apb2_peripheral_bit_t bit);

// Disable an APB2 peripheral
void rcc_apb2_disable(rcc_apb2_peripheral_bit_t bit);