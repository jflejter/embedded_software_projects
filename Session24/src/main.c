//
// COMP-GENG 421 - Tom Lupfer
//
// Session 24 - Rendering and animating the paddles
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

	// Render the paddles in their initial position
	LcdRenderObject(LCD_OBJ_PADDLE, 0, 12);
	LcdRenderObject(LCD_OBJ_PADDLE, 124, 12);

	// Render the ball in the center of the display
	LcdRenderObject(LCD_OBJ_BALL, 60, 12);

	// Main loop
	while(TRUE)
	{
		// Wait for tick timer
		ClockWaitForTick();

		// Clock the state machines
DBG_SET();
//		AdcClock();
		RgbClock();
DBG_CLR();

	}	// End - main loop
}
