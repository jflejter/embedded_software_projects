// COMP-GENG 421 - Tom Lupfer
//
// Session 1 – LED blink via software delay loop
//
// GPIO B4 -> Red LED (active low)
//
#include "stm32l1xx.h"
#include "stm32l1xx_nucleo.h"
#include "stm32l1xx_ll_bus.h"
#include "stm32l1xx_ll_gpio.h"
// ^ ^
// | |
// | ell ell --> low-level driver
// |
// ell one -------> STM32L1xx family of microprocessors
#define FALSE 0 // Boolean false
#define TRUE 1 // Boolean true
#define GPIO_PIN4 4 // GPIO pin 4 index
#define GPIO_PIN4_BITMASK (1 << GPIO_PIN4) // GPIO pin 4 bitmask
int main(void)
{
	volatile int DelayCnt;

	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // enable the GPIOB port clock
	GPIOB->ODR &= ~GPIO_PIN4_BITMASK; // set PB4 low
	GPIOB->MODER = (1 << 8); // configure PB4 as an output

	// Main loop
	while(TRUE)
	{
		GPIOB->ODR ^= GPIO_PIN4_BITMASK; // toggle PB4

		// Delay for the on/off period
		for (DelayCnt = 0; DelayCnt < 20000; DelayCnt++)
			;

	} // End - main loop
}
