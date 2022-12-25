/*
 * pedal_hal.c
 *
 *  Created on: Dec 24, 2022
 *      Author: bruno
 */

#include "pedal_hal.h"

uint32_t inputBuffer[DOUBLE_BUFFER_SIZE];
uint32_t outputBuffer[DOUBLE_BUFFER_SIZE];

/*********************************************** Pedal HAL data structure *********************************************************/

typedef struct {
    ADC_HandleTypeDef* adc;
    DAC_HandleTypeDef* dac;
    uint32_t* in;
    uint32_t* out;
    bool isDataReady;
}PedalHal;

PedalHal ctx = { 0 };

/*********************************************** Pedal ST HAL asbtraction **********************************************************/

static void pedalHalStartAdcDma(void)
{
    HAL_ADC_Start_DMA(ctx.adc, &inputBuffer[0], DOUBLE_BUFFER_SIZE);
}

void pedalHalInit(ADC_HandleTypeDef* adc, DAC_HandleTypeDef* dac)
{
    ctx.adc = adc;
    ctx.dac = dac;
    pedalHalStartAdcDma();
}

void pedalHalProcessData(void)
{
    if (ctx.isDataReady)
    {
        for (unsigned i = 0; i < (DOUBLE_BUFFER_SIZE / 2); i++)
        {
            pedalOutputTask(&ctx.in[i], &ctx.out[i]);
        }
        HAL_DAC_Start_DMA(ctx.dac, DAC_CHANNEL_1, &ctx.out[0], (DOUBLE_BUFFER_SIZE / 2), DAC_ALIGN_12B_R);
        ctx.isDataReady = false;
    }
}

/**************************************************** ST HAL Callbacks ***************************************************************/

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(hadc == ctx.adc)
    {
        ctx.in = &inputBuffer[DOUBLE_BUFFER_SIZE / 2];
        ctx.out = &outputBuffer[DOUBLE_BUFFER_SIZE / 2];
        ctx.isDataReady = true;
    }
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(hadc == ctx.adc)
    {
        ctx.in = &inputBuffer[0];
        ctx.out = &outputBuffer[0];
        ctx.isDataReady = true;
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == ROTARY_SW_Pin)
        swEncoderIsr();
    else if(GPIO_Pin == ROTARY_A_Pin)
        rotaryEncoderIsr();
}
