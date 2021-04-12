/*
 * rotary_encoder.c
 *
 *  Created on: Feb 22, 2021
 *      Author: bruno
 */
#include "rotary_encoder.h"
#include <stdbool.h>

#define DEBOUNCE_TIME 3 // ms

typedef enum {
	ROTARY_PIN_A,
	ROTARY_PIN_B
}RotaryPin;

RotaryEncoderCtx rotaryEncoder;

void rotaryEncoderInit(RotaryGpioPort portA, RotaryGpioPin pinA, RotaryGpioPort portB, RotaryGpioPin pinB, RotaryGpioPort portSw, RotaryGpioPin pinSw,
						void (*incrementHandler)(void), void (*decrementHandler)(void))
{
	rotaryEncoder.aPort = portA;
	rotaryEncoder.aPin = pinA;
	rotaryEncoder.bPort = portB;
	rotaryEncoder.bPin = pinB;
	rotaryEncoder.swPort = portSw;
	rotaryEncoder.swPin = pinSw;
	rotaryEncoder.onIncrement = incrementHandler;
	rotaryEncoder.onDecrement = decrementHandler;
}

void rotartEncoderIsr(void)
{
	if((HAL_GPIO_ReadPin(rotaryEncoder.aPort, rotaryEncoder.aPin) == GPIO_PIN_RESET) && !rotaryEncoder.isDebounce)
	{
		rotaryEncoder.isDebounce = true;
		rotaryEncoder.debounce.startTicks = HAL_GetTick();
	}
}

void rotaryEncoderTask(void)
{
	if(rotaryEncoder.isDebounce)
	{
		if((HAL_GetTick() - rotaryEncoder.debounce.startTicks) >= DEBOUNCE_TIME)
		{
			rotaryEncoder.isDebounce = false;
			RotaryPinState currentA = HAL_GPIO_ReadPin(rotaryEncoder.aPort, rotaryEncoder.aPin);
			RotaryPinState currentB = HAL_GPIO_ReadPin(rotaryEncoder.bPort, rotaryEncoder.bPin);

			if(currentA)
				return;

			if(currentA == currentB)
			{
				if(rotaryEncoder.onIncrement != NULL)
					rotaryEncoder.onIncrement();
				rotaryEncoder.count++;
			}
			else
			{
				if(rotaryEncoder.onDecrement != NULL)
					rotaryEncoder.onDecrement();
				rotaryEncoder.count--;
			}
		}
	}
}
