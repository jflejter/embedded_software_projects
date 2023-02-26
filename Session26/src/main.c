//
// COMP-GENG 421 - Tom Lupfer
//
// Session 26 - Controlling the Pong paddles via the potentiometers
//

#include "main.h"
#include "adc.h"
#include "clock.h"
#include "dbg.h"
#include "lcd.h"
#include "pong.h"
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

	// Initialize the pong game
	PongInit();

	// Main loop
	while(TRUE)
	{
		// Wait for tick timer
		ClockWaitForTick();

		// Clock the state machines
DBG_SET();
		PongClock();
		RgbClock();
DBG_CLR();

	}	// End - main loop
}
