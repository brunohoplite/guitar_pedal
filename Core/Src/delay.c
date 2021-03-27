/*
 * delay.c
 *
 *  Created on: Mar 11, 2021
 *      Author: bruno
 */
#include "delay.h"

#define MAX_DELAY_BUFFER 4000
int32_t guitarBuffer[MAX_DELAY_BUFFER] = { 0 };
unsigned i = 0, j = 1;

uint32_t delay(uint32_t guitarOut, uint32_t dcBias)
{
	int32_t unBiased = guitarOut - dcBias;

	int32_t out = unBiased + ((2 * guitarBuffer[j]) / 5);
	guitarBuffer[i] = out;
	if(++i >= MAX_DELAY_BUFFER) i = 0;
	if(++j >= MAX_DELAY_BUFFER) j = 0;

	return out + dcBias;
}
