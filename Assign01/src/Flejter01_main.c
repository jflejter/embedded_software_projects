//
// COMP_GENG 421 - Tom Lupfer
//
// Session 3 - State machine concepts
//

#include "stm32l1xx.h"
#include "stm32l1xx_nucleo.h"


#define FALSE 0
#define TRUE 1

#define GPIO_PIN1 1 // GPIO pin 1 index
#define GPIO_PIN1_BITMASK (1 << GPIO_PIN1) // GPIO pin 1 bitmask
#define GPIO_PIN7 7 // GPIO pin 7 index
#define GPIO_PIN7_BITMASK (1 << GPIO_PIN7) // GPIO pin 7 bitmask

#define DBG_CLR() (GPIOB->ODR &= ~GPIO_PIN1_BITMASK)
#define DBG_SET() (GPIOB->ODR |= GPIO_PIN1_BITMASK)

#define LED_GRN_DIS() (GPIOC->ODR |= GPIO_PIN7_BITMASK)
#define LED_GRN_ENA() (GPIOC->ODR &= ~GPIO_PIN7_BITMASK)

#define LED_TICKS_OFF1 50
#define LED_TICKS_ON1 100
#define LED_TICKS_OFF2 200
#define LED_TICKS_ON2 300

#define LED_ST_OFF1 0
#define LED_ST_ON1 1
#define LED_ST_OFF2 2
#define LED_ST_ON2 3

#define TICK_DLY_CNT 200

void GpioInit(void);
void LedClock(void);

int main(void)
{
	volatile int TickCnt;

	// Initialize the hardware
	GpioInit();

	// Main loop
	while(TRUE)
	{
		// Delay for a 1 msec state machine tick
		for (TickCnt = 0; TickCnt < TICK_DLY_CNT; TickCnt++)
			;

		// Clock the LED state machine, measure its duration
		DBG_SET();
		LedClock();
		DBG_CLR();

	} // End - main loop
}


void GpioInit(void)
{
	// Enable the clock to GPIO ports B & C
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN;

	// GPIO PB1 -> Debug pin
	// Initialize PB1 to an output, low
	GPIOB->ODR &= ~GPIO_PIN1_BITMASK;
	GPIOB->MODER = (1 << (2 * GPIO_PIN1));

	// GPIO PC7 -> Green LED (active low)
	// Initialize PC7 to an output, high (green LED off)
	GPIOC->ODR |=  GPIO_PIN7_BITMASK;
	GPIOC->MODER = (1 << (2 * GPIO_PIN7));
}


void LedClock(void)
{
	static int	LedBlinkCnt = LED_TICKS_OFF1;
	static int	LedState = LED_ST_OFF1;

	// Clock the LED state machine
	switch(LedState)
	{
	case LED_ST_OFF1:
		if (--LedBlinkCnt <= 0)
		{
			LED_GRN_ENA();
			LedBlinkCnt = LED_TICKS_ON1;
			LedState = LED_ST_ON1;
		}
		break;

	case LED_ST_ON1:
		if (--LedBlinkCnt <= 0)
		{
			LED_GRN_DIS();
			LedBlinkCnt = LED_TICKS_OFF2;
			LedState = LED_ST_OFF2;
		}
		break;

	case LED_ST_OFF2:
		if (--LedBlinkCnt <= 0)
		{
			LED_GRN_ENA();
			LedBlinkCnt = LED_TICKS_ON2;
			LedState = LED_ST_ON2;
		}
		break;

	case LED_ST_ON2:
		if (--LedBlinkCnt <= 0)
		{
			LED_GRN_DIS();
			LedBlinkCnt = LED_TICKS_OFF1;
			LedState = LED_ST_OFF1;
		}
		break;
	}
}
