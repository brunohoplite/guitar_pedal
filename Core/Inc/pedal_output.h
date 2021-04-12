/*
 * pedal_output.h
 *
 *  Created on: Apr 11, 2021
 *      Author: bruno
 */

#ifndef INC_PEDAL_OUTPUT_H_
#define INC_PEDAL_OUTPUT_H_

#include "main.h"

void pedalOutputTask(ADC_HandleTypeDef* hadc, DAC_HandleTypeDef* hdac);

#endif /* INC_PEDAL_OUTPUT_H_ */
