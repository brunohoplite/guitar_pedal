/*
 * distortion.c
 *
 *  Created on: Mar 11, 2021
 *      Author: bruno
 */
#include <math.h>
#include "distortion.h"

unsigned gain = 10;
float boost = 2;
float divider = 248.f;

uint32_t distortion(uint32_t guitarOut, uint32_t dcBias)
{
	float out = (float)guitarOut - (float)dcBias;
#if 1
	out /= divider;
	float sign;
	if(out < 0)
		sign = -1.f;
	else
	{
		sign = 1;
		out *= -1.f;
	}
	out *= (float)gain;
	float distorted = 1 - exp(out);
	distorted *= sign;
	distorted *= boost;

	return (uint32_t)((distorted) * divider) + dcBias;
#else
	if(1)
	{
		if(out > 100)
		{
			float distorted = 100;
			return (uint32_t)distorted + dcBias;
		}
		else if(out < -100.f)
		{
			float distorted = -100.f;
			distorted += (float)dcBias;
			return (uint32_t)distorted;
		}
		else
			return out + dcBias;
	}
	else
		return out + dcBias;
#endif
}

const unsigned getDistortionGainValue(void)
{
	return gain;
}

unsigned* getDistortionGain(void)
{
	return &gain;
}
