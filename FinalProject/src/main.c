//
// COMP-GENG 421 - Tom Lupfer
//
// Final Project - Pong Game
//

#include "main.h"
#include "adc.h"
#include "clock.h"
#include "dbg.h"
#include "lcd.h"
#include "nav.h"
#include "pong.h"
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
	NavInit();

	// Main loop
	while(TRUE)
	{
		// Wait for tick timer
		ClockWaitForTick();

		// Clock the state machines
DBG_SET();
		NavClock();
		PongClock();
DBG_CLR();

	}	// End - main loop
}
