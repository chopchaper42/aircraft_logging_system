typedef unsigned long uint32_t;

#define FLASH_BASE          0x08000000
#define SRAM_BASE           0x20000000
#define PERIPHERALS_BASE    0x40000000

#define SRAM_SIZE           128 * 1024  // 128 kB of RAM
#define SRAM_END            (SRAM_BASE + SRAM_SIZE)

#define RCC_BASE            (PERIPHERALS_BASE + 0x23800)
#define RCC_APB1ENR         ((uint32_t*)(RCC_BASE + 0x30))

#define GPIOA_BASE          (PERIPHERALS_BASE + 0x20000)
#define GPIOA_MODER         ((uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_ODR           ((uint32_t*)(GPIOA_BASE + 0x14))


void delay(uint32_t count);
int main(void);


/* global initialized variable --> goes to .bss */
volatile uint32_t dataVar = 0x3f;
volatile uint32_t bssVar;

const float vals[] = { 3.14, 0.43, 2.71 };

int main()
{
    /* enable clock on GPIOA and GPIOC */
    *RCC_APB1ENR = 0x1 | 0x4;
    /* PA5 as outpit pull-up */
    *GPIOA_MODER |= 0x400;

    //while(vals[0] >= 3.14)
    while(1)
    {
        *GPIOA_ODR = 0x20;
        delay(200000);
        *GPIOA_ODR = 0x0;
        delay(600000);
    }
}

void delay(uint32_t count)
{
    while(count--);
}