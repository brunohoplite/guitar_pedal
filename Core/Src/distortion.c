/*
 * distortion.c
 *
 *  Created on: Mar 11, 2021
 *      Author: bruno
 */
#include <math.h>
#include "distortion.h"

int32_t clippingP = 75, clippingN = -75, gain = 1;

uint32_t distortion(uint32_t guitarOut, uint32_t dcBias)
{
	float out = (float)guitarOut - (float)dcBias;
#if 0
	if(out >= clippingP)
		out = clippingP;
	else if(out <= clippingN)
		out = clippingN;
	return out;
#else
	out /= 4095.f;
	float sign = out < 0 ? -1 : 1;
	if(out > 0)
		out *= -1.f * gain;
	else
		out *= gain;
	float distorted = 1 - exp(out * gain);
	distorted *= sign;

	return (uint32_t)((distorted / gain) * 4096.f)+ dcBias;
#endif
}

void gainUp(void)
{
	gain++;
}
