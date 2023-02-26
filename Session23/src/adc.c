//
// COMP-GENG 421 - Tom Lupfer
//
// Analog-to-Digital Converter (ADC) module
//

#include "main.h"
#include "adc.h"
#include "lcd.h"

#define DEG_HIGH_ACC_MULT		10

#define DEG_MIN					0
#define DEG_MAX					270
#define DEG_HIGH_ACC_MIN		(DEG_MIN * DEG_HIGH_ACC_MULT)
#define DEG_HIGH_ACC_MAX		(DEG_MAX * DEG_HIGH_ACC_MULT)

#define HYST_DEG				2
#define HYST_DEG_HIGH_ACC		(HYST_DEG * DEG_HIGH_ACC_MULT)

#define RDG_MIN					0
#define RDG_MAX					4095	// 12-bit unsigned ADC reading

#define KNOB_ST_LEFT_GREATER	0
#define KNOB_ST_RIGHT_GREATER	1

#define TICKS_200MSEC			200		// ticks in 200 msec


static UInt AdcLeftReadingGet(void);
static UInt AdcRightReadingGet(void);
static UInt Rdg2DegHighAcc(UInt Rdg);


void AdcInit(void)
{
	// Enable the GPIOA port clock
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	// Configure PA0 as ADC_IN0 (left knob), PA1 as ADC_IN1 (right knob)
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_0, LL_GPIO_MODE_ANALOG);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_1, LL_GPIO_MODE_ANALOG);

	// Enable the clock for ADC1
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

	// Set the conversion trigger source to software start
	LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);

	// Configure for single conversion mode of a single channel
	LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);
	LL_ADC_REG_SetSequencerLength(ADC1, LL_ADC_REG_SEQ_SCAN_DISABLE);
	LL_ADC_REG_SetFlagEndOfConversion(ADC1, LL_ADC_REG_FLAG_EOC_UNITARY_CONV);
}


void AdcClock(void)
{
	static int KnobState = KNOB_ST_LEFT_GREATER;
	static int TickCount = TICKS_200MSEC;

	int LeftDegHighAcc;
	int RightDegHighAcc;

	// Update the ADC readings every 200 msec
	if (--TickCount > 0)
	{
		return;
	}
	TickCount = TICKS_200MSEC;

	LeftDegHighAcc = Rdg2DegHighAcc(AdcLeftReadingGet());
	RightDegHighAcc = Rdg2DegHighAcc(AdcRightReadingGet());

	switch (KnobState)
	{
	case KNOB_ST_LEFT_GREATER:
		if (RightDegHighAcc > (LeftDegHighAcc + HYST_DEG_HIGH_ACC))
		{
			KnobState = KNOB_ST_RIGHT_GREATER;
			break;
		}
		break;

	case KNOB_ST_RIGHT_GREATER:
		if (LeftDegHighAcc > (RightDegHighAcc + HYST_DEG_HIGH_ACC))
		{
			KnobState = KNOB_ST_LEFT_GREATER;
			break;
		}
		break;
	}

	if (KnobState == KNOB_ST_LEFT_GREATER)
	{
		LcdPrintf(0, 0, "L: %3d  R: %3d\n", LeftDegHighAcc / DEG_HIGH_ACC_MULT, RightDegHighAcc / DEG_HIGH_ACC_MULT);
	}
	else
	{
		LcdPrintf(0, 0, "R: %3d  L: %3d\n", RightDegHighAcc / DEG_HIGH_ACC_MULT, LeftDegHighAcc / DEG_HIGH_ACC_MULT);
	}
}


static UInt AdcLeftReadingGet(void)
{
	// Set the ADC channel
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_0);

	// Enable the ADC, wait for it to be ready
	LL_ADC_Enable(ADC1);
	while (!LL_ADC_IsActiveFlag_ADRDY(ADC1))
		;

	// Start the conversion, wait for it to complete
	LL_ADC_REG_StartConversionSWStart(ADC1);
	while (!LL_ADC_IsActiveFlag_EOCS(ADC1))
		;

	// Disable the ADC
	LL_ADC_Disable(ADC1);

	return LL_ADC_REG_ReadConversionData12(ADC1);
}


static UInt AdcRightReadingGet(void)
{
	// Set the ADC channel
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_1);

	// Enable the ADC, wait for it to be ready
	LL_ADC_Enable(ADC1);
	while (!LL_ADC_IsActiveFlag_ADRDY(ADC1))
		;

	// Start the conversion, wait for it to complete
	LL_ADC_REG_StartConversionSWStart(ADC1);
	while (!LL_ADC_IsActiveFlag_EOCS(ADC1))
		;

	// Disable the ADC
	LL_ADC_Disable(ADC1);

	return LL_ADC_REG_ReadConversionData12(ADC1);
}


static UInt Rdg2DegHighAcc(UInt Rdg)
{
	return (Rdg * (DEG_HIGH_ACC_MAX - DEG_HIGH_ACC_MIN)) / (RDG_MAX - RDG_MIN);
}
