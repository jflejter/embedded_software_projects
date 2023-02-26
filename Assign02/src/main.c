//
// COMP-GENG 421 - Jared Flejter
//
// Session 6 - Pulse Width Modulation
//

#include <Flejter02_colors.h>
#include "main.h"
#include "clock.h"
#include "dbg.h"
#include "rgb.h"


int main(void)
{
	// Initialize the hardware
	ClockInit();
	DbgInit();
	RgbInit();

	// THL to demo PWM - remove when ColorsClock() is implemented
	//RgbGrnPwmSet(1);

	// Main loop
	while(TRUE)
	{
		// Wait for tick timer
		ClockWaitForTick();

		// Clock the state machines
		DBG_SET();
		ColorsClock();
		RgbClock();
		DBG_CLR();

	}	// End - main loop
}
