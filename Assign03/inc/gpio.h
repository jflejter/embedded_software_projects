//
// COMP-GENG 421 - Tom Lupfer
//
// GPIO module header file
//

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32l1xx_ll_bus.h"
#include "stm32l1xx_ll_gpio.h"


#define GPIO_PA9_CLR()		(LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_9))
#define GPIO_PA9_SET()		(LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_9))
#define GPIO_PA9_TOG()		(LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_9))

#define GPIO_PB4_CLR()		(LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_4))
#define GPIO_PB4_SET()		(LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4))
#define GPIO_PB4_TOG()		(LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_4))

#define GPIO_PC4_CLR()		(LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_4))
#define GPIO_PC4_SET()		(LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_4))
#define GPIO_PC4_TOG()		(LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_4))

#define GPIO_PC7_CLR()		(LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_7))
#define GPIO_PC7_SET()		(LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_7))
#define GPIO_PC7_TOG()		(LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_7))

#define GPIO_PB5_IS_SET()	(LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_5))


void GpioInit(void);

#endif	// GPIO_H_
