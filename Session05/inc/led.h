//
// COMP-GENG 421 - Tom Lupfer
//
// LED module header file
//

#ifndef LED_H_
#define LED_H_

#define LED_DIS()		(LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_7))
#define LED_ENA()		(LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_7))
#define LED_TOG()		(LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_7))


void LedInit(void);
void LedClock(void);

#endif	// LED_H_
