/*
 * rotary_encoder.h
 *
 *  Created on: Feb 22, 2021
 *      Author: bruno
 */

#ifndef INC_ROTARY_ENCODER_H_
#define INC_ROTARY_ENCODER_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>

#define RotaryGpioPort GPIO_TypeDef*
#define RotaryGpioPin uint16_t
#define RotaryPinState GPIO_PinState

typedef struct {
	RotaryGpioPort aPort;
	RotaryGpioPin aPin;
	RotaryGpioPort bPort;
	RotaryGpioPin bPin;
	RotaryGpioPort swPort;
	RotaryGpioPin swPin;
	RotaryPinState lastApin;
	signed count;
	void(*onIncrement)(void);
	void(*onDecrement)(void);
	bool isDebounce;
	struct {
		uint32_t startTicks;
		RotaryPinState pinState;
	}debounce;
}RotaryEncoderCtx;

void rotaryEncoderInit(RotaryGpioPort portA, RotaryGpioPin pinA, RotaryGpioPort portB, RotaryGpioPin pinB, RotaryGpioPort portSw, RotaryGpioPin pinSw, void (*incrementHandler)(void), void (*decrementHandler)(void));
void rotartEncoderIsr(void);
void rotaryEncoderTask(void);

#endif /* INC_ROTARY_ENCODER_H_ */
