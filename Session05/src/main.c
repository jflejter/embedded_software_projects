//
// COMP-GENG 421 - Tom Lupfer
//
// Session 5 - Software vs hardware tick timer, switch debounce
//

#include "main.h"
#include "clock.h"
#include "dbg.h"
#include "led.h"
#include "nav.h"


#define SW_TIMER

#define TICK_1MSEC		2450


int main(void)
{
	volatile int	TickCnt;

	// Initialize the hardware
	ClockInit();
	DbgInit();
	LedInit();
	NavInit();

	// Main loop
	while(TRUE)
	{
#ifdef SW_TIMER
		// Delay for a 1 msec state machine tick
		for (TickCnt = 0; TickCnt < TICK_1MSEC; TickCnt++)
			;
#else	// !SW_TIMER
		// Wait for tick timer
		ClockWaitForTick();
#endif	// !SW_TIMER

		// Clock the state machines
		DBG_SET();
		LedClock();
		NavClock();
		DBG_CLR();

	}	// End - main loop
}
