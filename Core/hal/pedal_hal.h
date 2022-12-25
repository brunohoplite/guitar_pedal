/*
 * pedal_hal.h
 *
 *  Created on: Dec 24, 2022
 *      Author: bruno
 */

#ifndef HAL_PEDAL_HAL_H_
#define HAL_PEDAL_HAL_H_

#include "lcd.h"
#include "rotary_encoder.h"
#include "user_menu.h"
#include "pedal_output.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#define DOUBLE_BUFFER_SIZE 1024

void pedalHalInit(ADC_HandleTypeDef* adc, DAC_HandleTypeDef* dac);

#endif /* HAL_PEDAL_HAL_H_ */
