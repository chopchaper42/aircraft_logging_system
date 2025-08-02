#include <stdint.h>

/*
*   Structure with memory layout: 4B 4B 4B 4B ...
*   Every register takes 4B of memory (see documentation) - so we use 32-bit integer to represent one register.
*   Every GPIO has 10 registers. Those are the following:
*/
struct  gpio {
    volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFRL, AFRH
};

/*
*   GPIOA is a structure starting at the memory address 0x40020000 (bank A address in the documentation).
*/
#define GPIOA ((struct gpio *) 0x40020000)

/*
*   MODER REGISTER
*   INPUT = 00 = 0, OUTPUT = 01 = 1, ALTERNATE = 10 = 2, ANALOGUE = 11 = 3
*/
enum { GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_ALTERNATE, GPIO_MODE_ANALOGUE };

/*
*   OTYPER REGISTER 
*   PUSH_PULL = 0, OPEN_DRAIN = 1
*/
enum { OUTPUT_TYPE_PUSH_PULL, OUTPUT_TYPE_OPEN_DRAIN };