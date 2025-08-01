typedef unsigned long uint32_t;

#define SRAM_BASE           0x20000000

#define SRAM_SIZE           128 * 1024  // 128 kB of RAM
#define SRAM_END            (SRAM_BASE + SRAM_SIZE)

// Defined in the linker script:
// Begin address for the initalization values of the .data section.
extern uint32_t _sidata;
// Begin address for the .data section
extern uint32_t _sdata;
// End address for the .data section
extern uint32_t _edata;

// Defined in the .bss section
extern uint32_t _sbss;
extern uint32_t _ebss;

inline void __initialize_data(uint32_t *flash_begin, uint32_t *data_begin, uint32_t *data_end);
void _start(void);
extern int main(void);


/* minimal vector table */
uint32_t *vector_table[] __attribute__((section(".isr_vector"))) =
{
    (uint32_t *)SRAM_END, /* stach pointer */
    (uint32_t *)_start      /* application entry point */
};

void __initialize_data(uint32_t *flash_begin, uint32_t *data_begin, uint32_t *data_end)
{
    uint32_t *p = data_begin;
    while (p < data_end)
    {
        *p++ = *flash_begin++;
    }
}

void __initialize_bss(uint32_t *bss_begin, uint32_t *bss_end)
{
    uint32_t *p = bss_begin;
    while (p < bss_end)
        *p++ = 0;
}

void __attribute__((noreturn, weak)) _start(void)
{
    __initialize_data(&_sidata, &_sdata, &_edata);
    __initialize_bss(&_sbss, &_ebss);
    main();

    for(;;);
}