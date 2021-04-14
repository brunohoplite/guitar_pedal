/*
 * rotary_encoder.c
 *
 *  Created on: Feb 22, 2021
 *      Author: bruno
 */
#include "rotary_encoder.h"
#include <stdbool.h>

#define ROTARY_DEBOUNCE_TIME 3  // ms
#define SW_DEBOUNCE_TIME 	 75 // ms

enum {
	DEBOUCNE_ROTARY = 0,
	DEBOUNCE_SW = 1
}Debounce;

typedef enum {
	ROTARY_PIN_A,
	ROTARY_PIN_B
}RotaryPin;

RotaryEncoderCtx rotaryEncoder;

void rotaryEncoderInit(RotaryGpioPort portA, RotaryGpioPin pinA, RotaryGpioPort portB, RotaryGpioPin pinB, RotaryGpioPort portSw, RotaryGpioPin pinSw,
						void (*incrementHandler)(void), void (*decrementHandler)(void), void (*swPressedHandler)(void))
{
	rotaryEncoder.aPort = portA;
	rotaryEncoder.aPin = pinA;
	rotaryEncoder.bPort = portB;
	rotaryEncoder.bPin = pinB;
	rotaryEncoder.swPort = portSw;
	rotaryEncoder.swPin = pinSw;
	rotaryEncoder.onIncrement = incrementHandler;
	rotaryEncoder.onDecrement = decrementHandler;
	rotaryEncoder.onSwPressed = swPressedHandler;
}

void rotaryEncoderIsr(void)
{
	if((HAL_GPIO_ReadPin(rotaryEncoder.aPort, rotaryEncoder.aPin) == GPIO_PIN_RESET) && !rotaryEncoder.debounce[DEBOUCNE_ROTARY].isDebounce)
	{
		rotaryEncoder.debounce[DEBOUCNE_ROTARY].isDebounce = true;
		rotaryEncoder.debounce[DEBOUCNE_ROTARY].startTicks = HAL_GetTick();
	}
}

void swEncoderIsr(void)
{
	if(!rotaryEncoder.debounce[DEBOUNCE_SW].isDebounce)
	{
		rotaryEncoder.debounce[DEBOUNCE_SW].isDebounce = true;
		rotaryEncoder.debounce[DEBOUNCE_SW].startTicks = HAL_GetTick();
	}
}

void rotaryEncoderTask(void)
{
	if(rotaryEncoder.debounce[DEBOUCNE_ROTARY].isDebounce)
	{
		if((HAL_GetTick() - rotaryEncoder.debounce[DEBOUCNE_ROTARY].startTicks) >= ROTARY_DEBOUNCE_TIME)
		{
			rotaryEncoder.debounce[DEBOUCNE_ROTARY].isDebounce = false;
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

	if(rotaryEncoder.debounce[DEBOUNCE_SW].isDebounce)
	{
		if((HAL_GetTick() - rotaryEncoder.debounce[DEBOUNCE_SW].startTicks) >= SW_DEBOUNCE_TIME && HAL_GPIO_ReadPin(rotaryEncoder.swPort, rotaryEncoder.swPin) == GPIO_PIN_RESET)
		{
			rotaryEncoder.debounce[DEBOUNCE_SW].isDebounce = false;
			rotaryEncoder.onSwPressed();
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		}
	}
}
