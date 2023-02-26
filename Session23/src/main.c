//
// COMP-GENG 421 - Tom Lupfer
//
// Session 19 - Rendering characters on the LCD
//

#include "main.h"
#include "adc.h"
#include "clock.h"
#include "dbg.h"
#include "lcd.h"
#include "rgb.h"
#include "spi.h"
#include "uart.h"


int main(void)
{
	// Initialize the MCU hardware required for debugging first
	ClockInit();
	DbgInit();
	UartInit();

	// Initialize the remaining MCU hardware
	AdcInit();
	SpiInit();

	// Initialize the external peripherals
	LcdInit();
	RgbInit();

	// Main loop
	while(TRUE)
	{
		// Wait for tick timer
		ClockWaitForTick();

		// Clock the state machines
DBG_SET();
		AdcClock();
		RgbClock();
DBG_CLR();

	}	// End - main loop
}
