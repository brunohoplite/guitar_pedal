/*
 * distortion.h
 *
 *  Created on: Mar 11, 2021
 *      Author: bruno
 */

#ifndef INC_DISTORTION_H_
#define INC_DISTORTION_H_

#include "main.h"

uint32_t distortion(uint32_t guitarOut, uint32_t dcBias);
const unsigned getDistortionGainValue(void);
unsigned* getDistortionGain(void);

#endif /* INC_DISTORTION_H_ */
