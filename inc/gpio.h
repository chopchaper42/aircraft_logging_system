#include <stdint.h>

/*
*   Structure with memory layout: 4B 4B 4B 4B ...
*   Every register takes 4B of memory (see documentation) - so we use 32-bit integer to represent one register.
*   Every GPIO has 10 registers. Those are the following:
*/
struct gpio {
    volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFRL, AFRH
};

/*
*   GPIOA is a structure starting at the memory address 0x40020000 (bank A address in the documentation).
*/
#define GPIOA               ((struct gpio *) 0x40020000)
#define GPIO(bank)          ((struct gpio *) 0x40020000 + (0x400 * (bank)))
#define PIN(bank, num)      ((((char) bank) - 'A') << 8 | ((uint8_t) num));
#define PINNO(pin)          (pin & 255) // pin: (0000 0111 0100 1100) & (0000 0000 1111 1111) = (0000 0000 0100 1100)
#define PINBANK(pin)        (pin >> 8)

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

/*
*   OSPEEDR REGISTER
*   LOW SPEED = 00 = 0, MEDIUM SPEED = 01 = 1, FAST SPEED = 10 = 2, HIGH SPEED = 11 = 3
*/
enum { OUTPUT_SPEED_LOW, OUTPUT_SPEED_MEDIUM, OUTPUT_SPEED_FAST, OUTPUT_SPEED_HIGH };

/*
*   PUPDR REGISTER
*   NO PULL UP, NO PULL DOWN = 00 = 0, PULL UP = 01 = 1, PULL DOWN = 10 = 2
*/
enum { OUTPUT_NO_UP_NO_DOWN, OUTPUT_PULL_UP, OUTPUT_PULL_DOWN };

/*
*   ODR REGISTER
*   LOW = 0, HIGH = 1
*/
typedef enum 
{ 
    LOW,
    HIGH 
} level_t;

// OLD VERSION: static inline void gpio_set_mode(struct gpio *gpio, uint8_t pin, uint8_t mode);
static inline void gpio_set_mode(uint16_t pin, uint8_t mode)
{
    struct gpio *gpio = GPIO(PINBANK(pin));

    gpio->MODER &= ~(3U << (pin * 2));
    gpio->MODER |= ((mode & 3U) << (pin * 2));
}

static inline void gpio_set(uint16_t pin, level_t value)
{
    struct gpio *gpio = GPIO(PINBANK(pin));

    /*if (value == LOW)
    {
        gpio->ODR &= ~(1 << pin);
        return;
    }
    gpio->ODR |= ((value & 127) << pin);*/

    if (value == HIGH)
    {
        gpio->BSRR |= (1U << pin);
    }
    else
    {
        gpio->BSRR |= (1U << (pin + 16));
    }
}

static inline uint32_t gpio_get(uint16_t pin)
{
    struct gpio *gpio = GPIO(PINBANK(pin));

    return ((gpio->IDR & (1U << pin)) >> pin);
}
