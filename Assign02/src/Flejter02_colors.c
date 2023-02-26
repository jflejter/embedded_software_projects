//
// COMP-GENG 421 - Jared Flejter
//
// RGB LED color effects module
//

#include <Flejter02_colors.h>
#include "main.h"

#define RED_UP 0
#define RED_DOWN 1

#define GRN_UP 2
#define GRN_DOWN 3

#define BLU_UP 4
#define BLU_DOWN 5

#define YEL_UP 6
#define YEL_DOWN 7

#define TEL_UP 8
#define TEL_DOWN 9

#define MAG_UP 10
#define MAG_DOWN 11

#define WHT_UP 12
#define WHT_DOWN 13

#define DLY_80MSEC 80

void ColorsClock(void)
{
	static int ColorState = RED_UP;
	static int PwmCount = 0;

	static int DelayCount = DLY_80MSEC;

	if (--DelayCount > 0)
	{
		return;
	}
	DelayCount = DLY_80MSEC;

	switch(ColorState)
	{
	case RED_UP:
		if (PwmCount < RGB_PWM_MAX)
		{
			PwmCount++;
			RgbRedPwmSet(PwmCount);
			RGB_RED_ENA();
			break;
		}
		else
		{
			ColorState = RED_DOWN;
			RGB_RED_ENA();
			break;
		}
		break;

	case RED_DOWN:
		if (PwmCount > RGB_PWM_OFF)
		{
			PwmCount--;
			RgbRedPwmSet(PwmCount);
			RGB_RED_ENA();
			break;
		}
		else
		{
			ColorState = GRN_UP;
			RGB_RED_DIS();
			break;
		}
		break;

	case GRN_UP:
		if (PwmCount < RGB_PWM_MAX)
		{
			PwmCount++;
			RgbGrnPwmSet(PwmCount);
			RGB_GRN_ENA();
			break;
		}
		else
		{
			ColorState = GRN_DOWN;
			RGB_GRN_ENA();
			break;
		}
		break;

	case GRN_DOWN:
		if (PwmCount > RGB_PWM_OFF)
		{
			PwmCount--;
			RgbGrnPwmSet(PwmCount);
			RGB_GRN_ENA();
			break;
		}
		else
		{
			ColorState = BLU_UP;
			RGB_GRN_DIS();
			break;
		}
		break;

	case BLU_UP:
		if (PwmCount < RGB_PWM_MAX)
		{
			PwmCount++;
			RgbBluPwmSet(PwmCount);
			RGB_BLU_ENA();
			break;
		}
		else
		{
			ColorState = BLU_DOWN;
			RGB_BLU_ENA();
			break;
		}
		break;

	case BLU_DOWN:
		if (PwmCount > RGB_PWM_OFF)
		{
			PwmCount--;
			RgbBluPwmSet(PwmCount);
			RGB_BLU_ENA();
			break;
		}
		else
		{
			ColorState = YEL_UP;
			RGB_BLU_DIS();
			break;
		}
		break;

	case YEL_UP:
		if (PwmCount < RGB_PWM_MAX)
		{
			PwmCount++;
			RgbRedPwmSet(PwmCount);
			RgbGrnPwmSet(PwmCount);
			RGB_RED_ENA();
			RGB_GRN_ENA();
			break;
		}
		else
		{
			ColorState = YEL_DOWN;
			RGB_RED_ENA();
			RGB_GRN_ENA();
			break;
		}
		break;

	case YEL_DOWN:
		if (PwmCount > RGB_PWM_OFF)
		{
			PwmCount--;
			RgbRedPwmSet(PwmCount);
			RgbGrnPwmSet(PwmCount);
			RGB_RED_ENA();
			RGB_GRN_ENA();
			break;
		}
		else
		{
			ColorState = TEL_UP;
			RGB_RED_DIS();
			RGB_GRN_DIS();
			break;
		}
		break;

	case TEL_UP:
		if (PwmCount < RGB_PWM_MAX)
		{
			PwmCount++;
			RgbBluPwmSet(PwmCount);
			RgbGrnPwmSet(PwmCount);
			RGB_BLU_ENA();
			RGB_GRN_ENA();
			break;
		}
		else
		{
			ColorState = TEL_DOWN;
			RGB_BLU_ENA();
			RGB_GRN_ENA();
			break;
		}
		break;

	case TEL_DOWN:
		if (PwmCount > RGB_PWM_OFF)
		{
			PwmCount--;
			RgbBluPwmSet(PwmCount);
			RgbGrnPwmSet(PwmCount);
			RGB_BLU_ENA();
			RGB_GRN_ENA();
			break;
		}
		else
		{
			ColorState = MAG_UP;
			RGB_BLU_DIS();
			RGB_GRN_DIS();
			break;
		}
		break;

	case MAG_UP:
		if (PwmCount < RGB_PWM_MAX)
		{
			PwmCount++;
			RgbRedPwmSet(PwmCount);
			RgbBluPwmSet(PwmCount);
			RGB_RED_ENA();
			RGB_BLU_ENA();
			break;
		}
		else
		{
			ColorState = MAG_DOWN;
			RGB_RED_ENA();
			RGB_BLU_ENA();
			break;
		}
		break;

	case MAG_DOWN:
		if (PwmCount > RGB_PWM_OFF)
		{
			PwmCount--;
			RgbRedPwmSet(PwmCount);
			RgbBluPwmSet(PwmCount);
			RGB_RED_ENA();
			RGB_BLU_ENA();
			break;
		}
		else
		{
			ColorState = WHT_UP;
			RGB_RED_DIS();
			RGB_BLU_DIS();
			break;
		}
		break;

	case WHT_UP:
		if (PwmCount < RGB_PWM_MAX)
		{
			PwmCount++;
			RgbRedPwmSet(PwmCount);
			RgbGrnPwmSet(PwmCount);
			RgbBluPwmSet(PwmCount);
			RGB_RED_ENA();
			RGB_GRN_ENA();
			RGB_BLU_ENA();
			break;
		}
		else
		{
			ColorState = WHT_DOWN;
			RGB_RED_ENA();
			RGB_GRN_ENA();
			RGB_BLU_ENA();
			break;
		}
		break;

	case WHT_DOWN:
		if (PwmCount > RGB_PWM_OFF)
		{
			PwmCount--;
			RgbRedPwmSet(PwmCount);
			RgbGrnPwmSet(PwmCount);
			RgbBluPwmSet(PwmCount);
			RGB_RED_ENA();
			RGB_GRN_ENA();
			RGB_BLU_ENA();
			break;
		}
		else
		{
			ColorState = RED_UP;
			RGB_RED_DIS();
			RGB_GRN_DIS();
			RGB_BLU_DIS();
			break;
		}
		break;
	}
}
