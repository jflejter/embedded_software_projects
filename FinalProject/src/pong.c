//
// COMP-GENG 421 - Tom Lupfer
//
// Pong game module
//

#include <stdlib.h>

#include "main.h"
#include "adc.h"
#include "dbg.h"
#include "lcd.h"
#include "nav.h"
#include "pong.h"

#include "eprintf.h"


#define PONG_ST_SPLASH_INIT		0
#define PONG_ST_SPLASH_LEVEL1	1
#define PONG_ST_SPLASH_LEVEL2	2
#define PONG_ST_SPLASH_LEVEL3	3

#define PONG_ST_PLAY_NEW_GAME	4
#define PONG_ST_PLAY_NEXT_POINT	5
#define PONG_ST_PLAY_DELAY		6
#define PONG_ST_PLAY			7

#define PONG_ST_RESULTS			8

#define LEVEL_1					0
#define LEVEL_2					1
#define LEVEL_3					2

#define ADC_DEG_CENTER			((ADC_DEG_MAX - ADC_DEG_MIN) / 2)
#define PADDLE_DEG_ACTIVE		120	// active degrees for paddle motion
#define PADDLE_DEG_MIN			(ADC_DEG_CENTER - (PADDLE_DEG_ACTIVE / 2))
#define PADDLE_DEG_MAX			(ADC_DEG_CENTER + (PADDLE_DEG_ACTIVE / 2))

#define BALL_POSX_MIN			LCD_PADDLE_PIXEL_WIDTH
#define BALL_POSX_MAX			(LCD_PIXEL_WIDTH - (LCD_BALL_PIXEL_WIDTH + LCD_PADDLE_PIXEL_WIDTH))
#define BALL_POSY_MIN			0
#define BALL_POSY_MAX			(LCD_PIXEL_HEIGHT - LCD_BALL_PIXEL_HEIGHT)

#define BALL_POSX_CENTER		((LCD_PIXEL_WIDTH / 2) - (LCD_BALL_PIXEL_WIDTH / 2))
#define BALL_POSY_CENTER		((LCD_PIXEL_HEIGHT / 2) - (LCD_BALL_PIXEL_HEIGHT / 2))

#define PADDLE_POSY_INVALID		-1
#define PADDLE_POSX_LEFT		0
#define PADDLE_POSX_RIGHT		(LCD_PIXEL_WIDTH - LCD_PADDLE_PIXEL_WIDTH)
#define PADDLE_POSY_MIN			0
#define PADDLE_POSY_MAX			(LCD_PIXEL_HEIGHT - LCD_PADDLE_PIXEL_HEIGHT)

#define UPDATE_TICKS			10						// 10 msec
#define DELAY_TICKS				(1500 / UPDATE_TICKS)	// 1.5 sec delay at start of each point

#define WINNING_SCORE			3


static Int BallCurPosX;
static Int BallNextPosX;
static Int BallCurPosY;
static Int DeltaX;
static Int IncrementX;
static Int IncrementY;
static Int PaddleCurLeftPosY;
static Int PaddleLastLeftPosY;
static Int PaddleCurRightPosY;
static Int PaddleLastRightPosY;
static Int Level;
static Int PaceDivider;
static Int ScoreLeft;
static Int ScoreRight;
static Bool ScoreNew;

// Update dividers to set the pace of the game
static const Int LevelArray[3] = {4, 3, 2};

// Array of X,Y pairs that breaks down to four sets of four pairs
// X value contains the number of pixels to move in the X direction before moving the number of pixels in the Y direction
// X and Y values are signed differently in the four sets
//   Set 1: +X, +Y (right and down)
//   Set 2: -X, +Y (left and down)
//   Set 3: +X, -Y (right and up)
//   Set 4: -X, -Y (left and up)
static const Int TrajectoryArray[16][2] = {{ 1,  1}, { 2,  1}, { 3,  1}, { 4,  1},
										   {-1,  1}, {-2,  1}, {-3,  1}, {-4,  1},
										   { 1, -1}, { 2, -1}, { 3, -1}, { 4, -1},
										   {-1, -1}, {-2, -1}, {-3, -1}, {-4, -1}};


static void ScoreUpdate(void);
static void PaddleUpdate(void);
static void BallUpdate(void);


void PongClock(void)
{
	static Int DelayCount;
	static Int PongState = PONG_ST_SPLASH_INIT;
	static UInt RandomNumberSeed;
	static Int UpdateTickCount = UPDATE_TICKS;

	Int TrajectoryIdx;

	// Seed will be the tick count from the splash screen to the start of the first game
	RandomNumberSeed++;

	// Update delay
	if (--UpdateTickCount > 0)
	{
		return;
	}
	UpdateTickCount = UPDATE_TICKS;

	switch (PongState)
	{
	case PONG_ST_SPLASH_INIT:
		LcdClear();
		LcdPrintf(0, 3, LCD_CHAR_NORMAL, "Jared's Pong Game");
		LcdPrintf(2, 2, LCD_CHAR_NORMAL, "Difficulty: ");
		LcdPrintf(2, 14, LCD_CHAR_REVERSE, "1");
		LcdPrintf(2, 16, LCD_CHAR_NORMAL, "2");
		LcdPrintf(2, 18, LCD_CHAR_NORMAL, "3");
		LcdPrintf(3, 0, LCD_CHAR_NORMAL, "Press Select to Play");
		NavClearLeftIsPressed();
		NavClearRightIsPressed();
		NavClearSelectIsPressed();
		Level = LEVEL_1;
		RandomNumberSeed = 0;
		PongState = PONG_ST_SPLASH_LEVEL1;
		break;

	case PONG_ST_SPLASH_LEVEL1:
		if (NavRightIsPressed())
		{
			NavClearLeftIsPressed();
			NavClearRightIsPressed();
			LcdPrintf(2, 14, LCD_CHAR_NORMAL, "1");
			LcdPrintf(2, 16, LCD_CHAR_REVERSE, "2");
			Level = LEVEL_2;
			PongState = PONG_ST_SPLASH_LEVEL2;
			break;
		}
		if (NavSelectIsPressed())
		{
			PongState = PONG_ST_PLAY_NEW_GAME;
			break;
		}
		break;

	case PONG_ST_SPLASH_LEVEL2:
		if (NavRightIsPressed())
		{
			NavClearLeftIsPressed();
			NavClearRightIsPressed();
			LcdPrintf(2, 16, LCD_CHAR_NORMAL, "2");
			LcdPrintf(2, 18, LCD_CHAR_REVERSE, "3");
			Level = LEVEL_3;
			PongState = PONG_ST_SPLASH_LEVEL3;
			break;
		}
		if (NavLeftIsPressed())
		{
			NavClearLeftIsPressed();
			NavClearRightIsPressed();
			LcdPrintf(2, 14, LCD_CHAR_REVERSE, "1");
			LcdPrintf(2, 16, LCD_CHAR_NORMAL, "2");
			Level = LEVEL_1;
			PongState = PONG_ST_SPLASH_LEVEL1;
			break;
		}
		if (NavSelectIsPressed())
		{
			PongState = PONG_ST_PLAY_NEW_GAME;
			break;
		}
		break;

	case PONG_ST_SPLASH_LEVEL3:
		if (NavLeftIsPressed())
		{
			NavClearLeftIsPressed();
			NavClearRightIsPressed();
			LcdPrintf(2, 16, LCD_CHAR_REVERSE, "2");
			LcdPrintf(2, 18, LCD_CHAR_NORMAL, "3");
			Level = LEVEL_2;
			PongState = PONG_ST_SPLASH_LEVEL2;
			break;
		}
		if (NavSelectIsPressed())
		{
			PongState = PONG_ST_PLAY_NEW_GAME;
			break;
		}
		break;

	case PONG_ST_PLAY_NEW_GAME:
		srand(RandomNumberSeed);	// seed the random number generator
		ScoreLeft = 0;
		ScoreRight = 0;
		PaceDivider = LevelArray[Level];
		PongState = PONG_ST_PLAY_NEXT_POINT;
		break;

	case PONG_ST_PLAY_NEXT_POINT:
		TrajectoryIdx = rand() & 0xf;	// limit trajectory index to 0-15
		DeltaX = TrajectoryArray[TrajectoryIdx][0];
		IncrementX = DeltaX > 0 ? 1 : -1;
		IncrementY = TrajectoryArray[TrajectoryIdx][1];
		BallCurPosX = BALL_POSX_CENTER;
		BallCurPosY = BALL_POSY_CENTER;
		BallNextPosX = BallCurPosX + DeltaX;
		LcdClear();
		LcdRenderObject(LCD_OBJ_BALL, BallCurPosX, BallCurPosY, LCD_OBJ_RENDER);
		ScoreNew = FALSE;
		PaddleLastLeftPosY = PADDLE_POSY_INVALID;	// invalid position => first render
		PaddleLastRightPosY = PADDLE_POSY_INVALID;	// invalid position => first render
		DelayCount = DELAY_TICKS;	// delay to start ball movement
		PongState = PONG_ST_PLAY_DELAY;
		break;

	case PONG_ST_PLAY_DELAY:
		ScoreUpdate();
		PaddleUpdate();
		if (--DelayCount > 0)
		{
			break;
		}
		DelayCount = PaceDivider;	// delay based on the difficulty level
		PongState = PONG_ST_PLAY;
		break;

	case PONG_ST_PLAY:
		if (--DelayCount > 0)
		{
			break;
		}
		DelayCount = PaceDivider;

		// Update the display
		ScoreUpdate();
		PaddleUpdate();
		BallUpdate();

		// Check for a winner
		if (ScoreLeft == WINNING_SCORE)
		{
			LcdClear();
			LcdPrintf(0, 0, LCD_CHAR_NORMAL, "WINNER!");
			LcdPrintf(0, 15, LCD_CHAR_NORMAL, "LOSER!");
			LcdPrintf(3, 0, LCD_CHAR_NORMAL, "Select To Play Again!");
			NavClearSelectIsPressed();
			PongState = PONG_ST_RESULTS;
			break;
		}
		if (ScoreRight == WINNING_SCORE)
		{
			LcdClear();
			LcdPrintf(0, 0, LCD_CHAR_NORMAL, "LOSER!");
			LcdPrintf(0, 14, LCD_CHAR_NORMAL, "WINNER!");
			LcdPrintf(3, 0, LCD_CHAR_NORMAL, "Select To Play Again!");
			NavClearSelectIsPressed();
			PongState = PONG_ST_RESULTS;
			break;
		}

		// Check for a score
		if (ScoreNew)
		{
			PongState = PONG_ST_PLAY_NEXT_POINT;
			break;
		}
		break;

	case PONG_ST_RESULTS:
		if (NavSelectIsPressed())
		{
			PongState = PONG_ST_SPLASH_INIT;
			break;
		}
		break;
	}
}


static void ScoreUpdate(void)
{
	LcdPrintf(0, 3, LCD_CHAR_NORMAL, "%d", ScoreLeft);
	LcdPrintf(0, 10, LCD_CHAR_NORMAL, "%d", Level + 1);
	LcdPrintf(0, 17, LCD_CHAR_NORMAL, "%d", ScoreRight);
}


static void PaddleUpdate(void)
{
	PaddleCurLeftPosY = ((AdcLeftDegGet() - PADDLE_DEG_MIN) * PADDLE_POSY_MAX) / PADDLE_DEG_ACTIVE;
	PaddleCurLeftPosY = PaddleCurLeftPosY < PADDLE_POSY_MIN ? PADDLE_POSY_MIN : PaddleCurLeftPosY;
	PaddleCurLeftPosY = PaddleCurLeftPosY > PADDLE_POSY_MAX ? PADDLE_POSY_MAX : PaddleCurLeftPosY;
	PaddleCurLeftPosY = PADDLE_POSY_MAX - PaddleCurLeftPosY;	// CW rotation => paddle goes up

	if (PaddleCurLeftPosY != PaddleLastLeftPosY)
	{
		if (PaddleLastLeftPosY != PADDLE_POSY_INVALID)
		{
			LcdRenderObject(LCD_OBJ_PADDLE, PADDLE_POSX_LEFT, PaddleLastLeftPosY, LCD_OBJ_ERASE);
		}
		LcdRenderObject(LCD_OBJ_PADDLE, PADDLE_POSX_LEFT, PaddleCurLeftPosY, LCD_OBJ_RENDER);
		PaddleLastLeftPosY = PaddleCurLeftPosY;
	}

	PaddleCurRightPosY = ((AdcRightDegGet() - PADDLE_DEG_MIN) * PADDLE_POSY_MAX) / PADDLE_DEG_ACTIVE;
	PaddleCurRightPosY = PaddleCurRightPosY < PADDLE_POSY_MIN ? PADDLE_POSY_MIN : PaddleCurRightPosY;
	PaddleCurRightPosY = PaddleCurRightPosY > PADDLE_POSY_MAX ? PADDLE_POSY_MAX : PaddleCurRightPosY;
	PaddleCurRightPosY = PADDLE_POSY_MAX - PaddleCurRightPosY;	// CW rotation => paddle goes up

	if (PaddleCurRightPosY != PaddleLastRightPosY)
	{
		if (PaddleLastRightPosY != PADDLE_POSY_INVALID)
		{
			LcdRenderObject(LCD_OBJ_PADDLE, PADDLE_POSX_RIGHT, PaddleLastRightPosY, LCD_OBJ_ERASE);
		}
		LcdRenderObject(LCD_OBJ_PADDLE,PADDLE_POSX_RIGHT, PaddleCurRightPosY, LCD_OBJ_RENDER);
		PaddleLastRightPosY = PaddleCurRightPosY;
	}
}


static void BallUpdate(void)
{
	//
	// Ball movement
	// Move ball X position by 1 pixel, see if Y position should move
	//
	LcdRenderObject(LCD_OBJ_BALL, BallCurPosX, BallCurPosY, LCD_OBJ_ERASE);
	BallCurPosX += IncrementX;
	if (BallCurPosX == BallNextPosX)
	{
		BallCurPosY += IncrementY;
		BallNextPosX = BallCurPosX + DeltaX;
	}
	LcdRenderObject(LCD_OBJ_BALL, BallCurPosX, BallCurPosY, LCD_OBJ_RENDER);

	//
	// Top wall collision (bounce: continue X direction, invert Y direction)
	//
	if ((BallCurPosY == BALL_POSY_MIN) && (IncrementY < 0))
	{
		IncrementY = -IncrementY;
	}

	//
	// Bottom wall collision (bounce: continue X direction, invert Y direction)
	//
	if ((BallCurPosY == BALL_POSY_MAX) && (IncrementY > 0))
	{
		IncrementY = -IncrementY;
	}

	//
	// Left goal line collision
	//
	if ((BallCurPosX == BALL_POSX_MIN) && (IncrementX < 0))
	{
		if (((PaddleCurLeftPosY + LCD_PADDLE_PIXEL_HEIGHT) < BallCurPosY      ) ||	// paddle above ball
			((BallCurPosY       + LCD_BALL_PIXEL_HEIGHT  ) < PaddleCurLeftPosY))	// ball above paddle
		{
			// No overlap with left paddle - score for right player
			ScoreRight++;
			ScoreNew = TRUE;
		}
		else
		{
			// Overlap with paddle - bounce: continue Y direction, invert X direction, reset X delta
			IncrementX = -IncrementX;
			DeltaX = -DeltaX;
			BallNextPosX = BallCurPosX + DeltaX;
		}
	}

	//
	// Right goal line collision
	//
	if ((BallCurPosX == BALL_POSX_MAX) && (IncrementX > 0))
	{
		if (((PaddleCurRightPosY + LCD_PADDLE_PIXEL_HEIGHT) < BallCurPosY       ) ||	// paddle above ball
			((BallCurPosY        + LCD_BALL_PIXEL_HEIGHT  ) < PaddleCurRightPosY))		// ball above paddle
		{
			// No overlap with right paddle - score for left player
			ScoreLeft++;
			ScoreNew = TRUE;
		}
		else
		{
			// Overlap with paddle - bounce: continue Y direction, invert X direction, reset X delta
			IncrementX = -IncrementX;
			DeltaX = -DeltaX;
			BallNextPosX = BallCurPosX + DeltaX;
		}
	}
}
