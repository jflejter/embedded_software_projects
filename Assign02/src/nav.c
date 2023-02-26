//
// COMP-GENG 421 - Jared Flejter
//
// Navigation switch module (only the Select button code is implemented)
//

#include "main.h"
#include "nav.h"


#define DEBOUNCE_TICKS		50			// debounce delay (50 msec)

#define SELECT_ST_RELEASED	0			// select button - released
#define SELECT_ST_PRESSED	1			// select button - pressed
#define SELECT_ST_DEBOUNCE	2			// select button - debounce

#define SELECT_IS_PRESSED()	(LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_5))


static Bool	SelectIsPressed = FALSE;	// select button pressed?


void NavInit(void)
{
	// Enable the clock for the PBx GPIO pins
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

	// PB5 <- select button (active high)
	// Initialize PB5 as an input
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_5, LL_GPIO_MODE_INPUT);
}


void NavClock(void)
{
	static int	SelectState = SELECT_ST_RELEASED;
	static int	SelectDebounceTickCnt;		// select button debounce tick count

	switch (SelectState)
	{
	case SELECT_ST_RELEASED:
		if (SELECT_IS_PRESSED())
		{
			SelectDebounceTickCnt = DEBOUNCE_TICKS;
			SelectState = SELECT_ST_DEBOUNCE;
		}
		break;

	case SELECT_ST_PRESSED:
		if (!SELECT_IS_PRESSED())
		{
			SelectDebounceTickCnt = DEBOUNCE_TICKS;
			SelectState = SELECT_ST_DEBOUNCE;
		}
		break;

	case SELECT_ST_DEBOUNCE:
		if (--SelectDebounceTickCnt >= 0)
		{
			break;
		}
		if (SELECT_IS_PRESSED())
		{
			SelectIsPressed = TRUE;
			SelectState = SELECT_ST_PRESSED;
		}
		else
		{
			SelectIsPressed = FALSE;
			SelectState = SELECT_ST_RELEASED;
		}
		break;
	}
}


Bool NavSelectIsPressed(void)
{
	return SelectIsPressed;
}


void NavClearSelectIsPressed(void)
{
	SelectIsPressed = FALSE;
}
