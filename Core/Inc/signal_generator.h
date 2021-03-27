/*
 * signal_generator.h
 *
 *  Created on: Dec 28, 2020
 *      Author: bruno
 */

#pragma once

#include "main.h"

#define numSamples  128
#define bigsample	1024

typedef enum {
	A_4 = 440,
	B_4 = 494,
	C_5 = 523,
	D_5 = 587,
	E_5 = 659,
	F_5 = 698,
	G_5 = 783,
	A_5 = 880,
	B_5 = 988,
	C_6 = 1047,
	Silence = 10,

	ALL_NOTES
}MusicNote;

const uint32_t sineWaveLut[numSamples];
uint32_t sineWaveScaledLut[numSamples];
uint32_t bigSine[bigsample];

void signalGeneratorPlayNote(MusicNote note);
void signalGeneratorInit(TIM_HandleTypeDef* htim);
void signalGeneratorStop(void);
void signalGeneratorPlayMusic(void);
void scaleSineWave(void);
