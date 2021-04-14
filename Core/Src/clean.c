/*
 * clean.c
 *
 *  Created on: Apr 13, 2021
 *      Author: bruno
 */
#include "clean.h"

uint32_t cleanLevel = 1;

uint32_t clean(uint32_t guitarOut, uint32_t dcBias)
{
	uint32_t out = guitarOut - dcBias;

	out *= cleanLevel;

	return out + dcBias;
}

const uint32_t getCleanLevelValue(void)
{
	return cleanLevel;
}

uint32_t* getCleanLevel(void)
{
	return &cleanLevel;
}

