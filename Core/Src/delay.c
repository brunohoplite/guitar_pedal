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

signed level = 6;

uint32_t delay(uint32_t guitarOut, uint32_t dcBias)
{
	int32_t unBiased = guitarOut - dcBias;

	int32_t delayed = ((level * guitarBuffer[j])) / 15;
	int32_t out = unBiased + delayed;
	guitarBuffer[i] = out;
	if(++i >= MAX_DELAY_BUFFER) i = 0;
	if(++j >= MAX_DELAY_BUFFER) j = 0;

	return out + dcBias;
}

const signed getDelayLevelValue(void)
{
	return level;
}

signed* getDelayLevel(void)
{
	return &level;
}
