/*
 * tuner.c
 *
 *  Created on: Sep 11, 2021
 *      Author: bruno
 */
#include "tuner.h"

#define LOW_E_FREQ	82.41f
#define A_FREQ		110.0f
#define D_FREQ		146.83f
#define G_FREQ		196.0f
#define B_FREQ		246.94f
#define E_FREQ		329.63f

#define TUNER_BUFF_LEN	4096

#define FFT_BUFF_LEN	TUNER_BUFF_LEN
#define MAGNITUDE_LEN	FFT_BUFF_LEN / 2
#define MAG_DCBEL_LEN	40

#define ACF_BUFF_LEN	2 * 4096

arm_rfft_fast_instance_f32 S;
const uint16_t fftLen = FFT_BUFF_LEN;
arm_status status;
float maxNsdf = 0, maxNsdfPeriod = 0;

typedef struct {
	float buffIn[TUNER_BUFF_LEN];
	unsigned buffIndex;
	float fftBuffOut[FFT_BUFF_LEN];
	float magnitude[MAGNITUDE_LEN];
	unsigned magDcbel[MAG_DCBEL_LEN];
	float maxValue;
	uint32_t maxIndex;
	NsdfState state;
	float nsdfFrequency;
}Tuner;

Tuner tunerData;

void tunerInit()
{
	status = arm_rfft_fast_init_f32(&S, fftLen);
	tunerData.state = FIRST_NEGATIVE_0_CROSSING;
}
#if FFT
static void tunerPerformFft(void)
{
	arm_rfft_fast_f32(&S, tunerData.buffIn, tunerData.fftBuffOut, 0);
	arm_cmplx_mag_f32(tunerData.fftBuffOut, tunerData.magnitude, MAGNITUDE_LEN);
	arm_max_f32(tunerData.magnitude, MAGNITUDE_LEN, &tunerData.maxValue, &tunerData.maxIndex);
	for(unsigned i = 0; i < MAG_DCBEL_LEN; i++)
		tunerData.magDcbel[i] = 20 * log10f(tunerData.magnitude[i]);
}
#else

static void tunerPerformNsdf(void)
{
	float correlationBuff[ACF_BUFF_LEN] = { 0 };

	arm_correlate_f32(tunerData.buffIn, FFT_BUFF_LEN, tunerData.buffIn, FFT_BUFF_LEN, correlationBuff);

	float mt1 = correlationBuff[TUNER_BUFF_LEN - 1], mt2 = correlationBuff[TUNER_BUFF_LEN - 1];

	tunerData.state = FIRST_NEGATIVE_0_CROSSING;

	for(unsigned i = TUNER_BUFF_LEN - 1; i < ACF_BUFF_LEN; i++)
	{
		correlationBuff[i] = 2 * correlationBuff[i] / (mt1 + mt2);
		mt1 -= tunerData.buffIn[ACF_BUFF_LEN - 1 - i] * tunerData.buffIn[ACF_BUFF_LEN - 1 - i];
		mt2 -= tunerData.buffIn[i] * tunerData.buffIn[i];

		switch(tunerData.state) {

		case FIRST_NEGATIVE_0_CROSSING:
			if(correlationBuff[i] < 0)
			{
				tunerData.state = FIRST_POSITIVE_0_CROSSING;
			}
			break;

		case FIRST_POSITIVE_0_CROSSING:
			if(correlationBuff[i] > 0)
			{
				tunerData.state = DETECT_PEAK;
				maxNsdf = correlationBuff[i];
			}
			break;

		case DETECT_PEAK:
			if(correlationBuff[i] > maxNsdf)
			{
				maxNsdf = correlationBuff[i];
				maxNsdfPeriod = i;
			}
			if(correlationBuff[i] < 0)
			{
				tunerData.state = SECOND_NEGATIVE_0_CROSSING;
			}
			break;

		case SECOND_NEGATIVE_0_CROSSING:
		default:
			break;
		}
	}
	maxNsdfPeriod = maxNsdfPeriod - 4096;
	if(maxNsdfPeriod > 50 && maxNsdfPeriod < 750)
		tunerData.nsdfFrequency = 44100.0f / maxNsdfPeriod;
	else if(maxNsdfPeriod == 0 || maxNsdfPeriod > 750)
		tunerData.nsdfFrequency = 0;
	maxNsdfPeriod = 4096;
}
#endif

void tuner(float sample)
{
	tunerData.buffIn[tunerData.buffIndex] = sample;
	if(++tunerData.buffIndex >= fftLen)
	{
#if FFT
		tunerPerformFft();
#else
		tunerPerformNsdf();
#endif
		tunerData.buffIndex = 0;
	}
}
