//
// COMP-GENG 421 - Jared Flejter
//
// Pong game module
//

#include "main.h"
#include "adc.h"
#include "lcd.h"
#include "pong.h"


#define UPDATE_TICKS		10	// update every 10 msec
#define LOWEST_ANGLE		75
#define HIGHEST_ANGLE		195
#define LOWEST_POSITION		24
#define HIGHEST_POSITION	0


void PongInit(void)
{
	// For now - render the ball in the center of the display
	LcdRenderObject(LCD_OBJ_BALL, 60, 12);
}


void PongClock(void)
{
	static Int UpdateTickCount = UPDATE_TICKS;
	static Int LastLeftPos = -1;	// invalid position => first render
	static Int LastRightPos = -1;	// invalid position => first render

	int LeftPaddlePosition;
	int RightPaddlePosition;
	if(AdcLeftDegGet() < LOWEST_ANGLE)
	{
		LeftPaddlePosition = LOWEST_POSITION;
	}
	else if(AdcLeftDegGet() > HIGHEST_ANGLE)
	{
		LeftPaddlePosition = HIGHEST_POSITION;
	}
	else
	{
		LeftPaddlePosition = LOWEST_POSITION - ((AdcLeftDegGet() - LOWEST_ANGLE) / 5);
	}
	if(AdcRightDegGet() < LOWEST_ANGLE)
	{
		RightPaddlePosition = LOWEST_POSITION;
	}
	else if(AdcRightDegGet() > HIGHEST_ANGLE)
	{
		RightPaddlePosition = HIGHEST_POSITION;
	}
	else
	{
		RightPaddlePosition =  LOWEST_POSITION - ((AdcRightDegGet() - LOWEST_ANGLE) / 5);
	}

	//Int CurrentPos;

	// Update delay
	if (--UpdateTickCount > 0)
	{
		return;
	}
	UpdateTickCount = UPDATE_TICKS;

	// Code to move the paddles goes here
	if (LeftPaddlePosition != LastLeftPos || RightPaddlePosition != LastRightPos)
	{
		LcdClear();
		LcdRenderObject(LCD_OBJ_BALL, 60, 12);
		LcdRenderObject(LCD_OBJ_PADDLE, 124, RightPaddlePosition); //right paddle
		LastRightPos = RightPaddlePosition;
		LcdRenderObject(LCD_OBJ_PADDLE, 0, LeftPaddlePosition); //left paddle
		LastLeftPos = LeftPaddlePosition;
	}

	// This may help you debug your paddle movement code
	LcdPrintf(0, 3, "%3d         %3d", AdcLeftDegGet(), AdcRightDegGet());

}
