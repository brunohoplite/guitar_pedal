/*
 * tuner.h
 *
 *  Created on: Sep 11, 2021
 *      Author: bruno
 */

#ifndef INC_TUNER_H_
#define INC_TUNER_H_

#include "main.h"

typedef enum {
	FIRST_NEGATIVE_0_CROSSING,
	FIRST_POSITIVE_0_CROSSING,
	DETECT_PEAK,
	SECOND_NEGATIVE_0_CROSSING
}NsdfState;

void tunerInit(void);
void tuner(float sample);

#endif /* INC_TUNER_H_ */
