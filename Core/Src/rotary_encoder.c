/*
 * rotary_encoder.c
 *
 *  Created on: Feb 22, 2021
 *      Author: bruno
 */
#include "rotary_encoder.h"
#include <stdbool.h>

typedef enum {
	ROTARY_PIN_A,
	ROTARY_PIN_B
}RotaryPin;

RotaryEncoderCtx rotaryEncoder;

int8_t lookup_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

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

bool up = false, down = false; uint16_t state = 0;
void rotartEncoderIsr(void)
{


#if 0
	if(currentA != rotaryEncoder.lastApin)
	{
		RotaryPinState currentB = HAL_GPIO_ReadPin(rotaryEncoder.bPort, rotaryEncoder.bPin);
		if(currentA != currentB)
		{
			if(up)
			{
				if(rotaryEncoder.onIncrement != NULL)
					rotaryEncoder.onIncrement();
				rotaryEncoder.count++;
				up = false;
			}
			else
				up = true;
		}
		else
		{
			if(down)
			{
				if(rotaryEncoder.onDecrement != NULL)
					rotaryEncoder.onDecrement();
				rotaryEncoder.count--;
				down = false;
			}
			else
				down = true;
		}

		rotaryEncoder.lastApin = currentA;
	}
#else
//	RotaryPinState currentB = HAL_GPIO_ReadPin(rotaryEncoder.bPort, rotaryEncoder.bPin);
//	if(currentA != currentB)
//	{
//		if(rotaryEncoder.onIncrement != NULL)
//			rotaryEncoder.onIncrement();
//		rotaryEncoder.count++;
//	}
//	else
//	{
//		if(rotaryEncoder.onDecrement != NULL)
//			rotaryEncoder.onDecrement();
//		rotaryEncoder.count--;
//	}

	if((HAL_GPIO_ReadPin(rotaryEncoder.aPort, rotaryEncoder.aPin) == GPIO_PIN_RESET) && !rotaryEncoder.isDebounce)
	{
		rotaryEncoder.isDebounce = true;
		rotaryEncoder.debounce.startTicks = HAL_GetTick();
	}

#endif
}

void rotaryEncoderTask(void)
{
	if(rotaryEncoder.isDebounce)
	{
		if((HAL_GetTick() - rotaryEncoder.debounce.startTicks) >= 3)
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
