/*
 * distortion.c
 *
 *  Created on: Mar 11, 2021
 *      Author: bruno
 */
#include <math.h>
#include "distortion.h"

unsigned gain = 10;

uint32_t distortion(uint32_t guitarOut, uint32_t dcBias)
{
	float out = (float)guitarOut - (float)dcBias;

	out /= 186.f;
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

	return (uint32_t)((distorted) * 186.f)+ dcBias;
}

const unsigned getDistortionGainValue(void)
{
	return gain;
}

unsigned* getDistortionGain(void)
{
	return &gain;
}
