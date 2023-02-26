//
// COMP-GENG 421 - Tom Lupfer
//
// Assignment 3 - UART Communications
//

#include <stdio.h>

#include "main.h"
#include "clock.h"
#include "dbg.h"
#include "gpio.h"
#include "uart.h"


int main(void)
{
	// Initialize the hardware
	ClockInit();
	GpioInit();
	UartInit();

#ifndef NEVER							// Section 1 - change to #ifndef to enable
	UartCharWrite('U');
	UartCharWrite('S');
	UartCharWrite('D');
	UartCharWrite(' ');
	UartCharWrite('C');
	UartCharWrite('O');
	UartCharWrite('M');
	UartCharWrite('P');
	UartCharWrite('-');
	UartCharWrite('G');
	UartCharWrite('E');
	UartCharWrite('N');
	UartCharWrite('G');
	UartCharWrite(' ');
	UartCharWrite('4');
	UartCharWrite('2');
	UartCharWrite('1');
	UartCharWrite('\n');
#endif	// NEVER

	printf("USD COMP-GENG 421\n");		// Section 2 - remove leftmost // to enable

	printf("USD COMP-GENG %d\n", 421);	// Section 3 - remove leftmost // to enable


	// Main loop
	while(TRUE)
	{
		// Wait for tick timer
		ClockWaitForTick();

		// Clock the state machines
		DBG_SET();
		printf("ABCDEFGHIJK\n");				// Section 4 - remove leftmost // to enable
		DBG_CLR();

	}	// End - main loop
}
