//
// COMP-GENG 421 - Tom Lupfer
//
// LED module (RGB green LED)
//

#include "main.h"
#include "led.h"
#include "nav.h"


#define JITTER_TICK_CNT		500

#define LED_ST_OFF			0
#define LED_ST_ON			1

#define LED_TICKS_OFF		400
#define LED_TICKS_ON		100


void LedInit(void)
{
	// Enable the clock for the PCx GPIO pins
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

	// GPIO PC7 -> RGB green LED (active low)
	// Initialize PC7 to an output, high (green LED off)
	LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_7);
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_7, LL_GPIO_MODE_OUTPUT);
}


void LedClock(void)
{
	static int		LedBlinkCnt = LED_TICKS_OFF;
	static int		LedState = LED_ST_OFF;

	volatile int	JitterCnt;

	// Clock the LED state machine
	// Add jitter when the button is pressed
	switch(LedState)
	{
	case LED_ST_OFF:
		if (--LedBlinkCnt <= 0)
		{
			LED_ENA();
			LedBlinkCnt = LED_TICKS_ON;
			LedState = LED_ST_ON;
		}
		break;

	case LED_ST_ON:
		if (NavSelectIsPressed())
		{
			for (JitterCnt = 0; JitterCnt < JITTER_TICK_CNT; JitterCnt++)
				;
		}
		if (--LedBlinkCnt <= 0)
		{
			LED_DIS();
			LedBlinkCnt = LED_TICKS_OFF;
			LedState = LED_ST_OFF;
		}
		break;
	}
}
