/*
 * pedal_output.c
 *
 *  Created on: Apr 11, 2021
 *      Author: bruno
 */
#include <stdbool.h>
#include <math.h>
#include "pedal_output.h"
#include "user_menu.h"
#include "delay.h"
#include "distortion.h"
#include "clean.h"

#define RMS_SAMPLES		100

const float alpha = 0.001f;

typedef struct {
	uint32_t guitarSignal;
	uint32_t out;
	unsigned count;
	float lastFilteredValue;
	float filteredValue;
	float actual;
	float squared;
	float rms;
	bool gateOn;
}GuitarPedal;

GuitarPedal pedal;

static void lowPassFilter(void)
{
	pedal.filteredValue = pedal.lastFilteredValue + alpha * (pedal.guitarSignal - pedal.lastFilteredValue);
	pedal.lastFilteredValue = pedal.filteredValue;
	pedal.actual = pedal.guitarSignal - pedal.lastFilteredValue;
}

static void calcultateRms(void)
{
	pedal.squared += pedal.actual * pedal.actual;
	if(++pedal.count >= RMS_SAMPLES)
	{
		pedal.count = 0;
		pedal.rms = pedal.squared / (float)RMS_SAMPLES;
		pedal.rms = sqrt(pedal.rms);
		pedal.squared = 0;
	}
}

static void processSelectedEffect(void)
{
	Menu currentMenu = getCurrentMenu();

	switch(currentMenu) {

	case  MENU_CLEAN:
		pedal.out = clean(pedal.guitarSignal, pedal.filteredValue);
		break;

	case  MENU_DELAY:
		pedal.out = delay(pedal.guitarSignal, pedal.filteredValue);
		break;

	case  MENU_DISTORTION:
		pedal.out = distortion(pedal.guitarSignal, pedal.filteredValue);
		break;
#ifdef FEATURE_TUNER
	case MENU_TUNER:
		pedal.out = 0;
#endif

	case MENU_START:
	case MENU_END:
	default:
		break;
	}
}

static void noiseGate(void)
{
#if 0
	if(rms < 20 && !gateOn)
	{
		gateOn = true;
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0);
	}
	else if(rms > 25 && gateOn)
		gateOn = false;

	if(gateOn)
		return;
#endif
}
void pedalOutputTask(uint32_t* in, uint32_t* out)
{
	pedal.guitarSignal = *in;
	lowPassFilter();
	calcultateRms();
	noiseGate();
	processSelectedEffect();
	*out = pedal.out;
}
