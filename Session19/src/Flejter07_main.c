//
// COMP-GENG 421 - Jared Flejter
//
// Session 19 - Rendering characters on the LCD
//

#include "main.h"
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
	SpiInit();

	// Initialize the external peripherals
	LcdInit();
	RgbInit();

	LcdPrintf(1, 4, "It Works %d%%", 100);
	// Main loop
	while(TRUE)
	{
		// Wait for tick timer
		ClockWaitForTick();

		// Clock the state machines
DBG_SET();
		RgbClock();
DBG_CLR();

	}	// End - main loop
}
