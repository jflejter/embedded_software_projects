//
// COMP-GENG 421 - Tom Lupfer
//
// GPIO module
//

#include "main.h"
#include "gpio.h"

void GpioInit(void)
{
	// Enable the port clocks
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

	// GPIO PA9 -> RGB blue LED (active low)
	// Initialize PA9 to an output, high (blue LED off)
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_9);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT);


	// GPIO PB4 -> RGB red LED (active low)
	// Initialize PB4 to an output, high (red LED off)
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_4, LL_GPIO_MODE_OUTPUT);

	// GPIO PB5 <- nav switch select button (active low)
	// Initialize PB5 to an input
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_5, LL_GPIO_MODE_INPUT);


	// GPIO PC4 -> Debug pin
	// Initialize PC4 to an output, low
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4);
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_4, LL_GPIO_MODE_OUTPUT);

	// GPIO PC7 -> RGB green LED (active low)
	// Initialize PC7 to an output, high (green LED off)
	LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_7);
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_7, LL_GPIO_MODE_OUTPUT);
}
