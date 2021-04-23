/*
 * delay.c
 *
 *  Created on: Mar 11, 2021
 *      Author: bruno
 */
#include "delay.h"

#define MAX_DELAY_BUFFER 4000

typedef struct {
	int32_t guitarBuffer[MAX_DELAY_BUFFER];
	unsigned i;
	unsigned j;
	signed delayLevel;
}DelayEffect;

DelayEffect delayCtx = {
		.guitarBuffer = { 0 },
		.i = 0,
		.j = 1,
		.delayLevel = 6
};

uint32_t delay(uint32_t guitarOut, uint32_t dcBias)
{
	int32_t unBiased = guitarOut - dcBias;

	int32_t delayed = ((delayCtx.delayLevel * delayCtx.guitarBuffer[delayCtx.j])) / 15;
	int32_t out = unBiased + delayed;
	delayCtx.guitarBuffer[delayCtx.i] = out;
	if(++delayCtx.i >= MAX_DELAY_BUFFER) delayCtx.i = 0;
	if(++delayCtx.j >= MAX_DELAY_BUFFER) delayCtx.j = 0;

	return out + dcBias;
}

const signed getDelayLevelValue(void)
{
	return delayCtx.delayLevel;
}

signed* getDelayLevel(void)
{
	return &delayCtx.delayLevel;
}
