/*
 * clean.h
 *
 *  Created on: Apr 13, 2021
 *      Author: bruno
 */

#ifndef INC_CLEAN_H_
#define INC_CLEAN_H_

#include "main.h"

uint32_t clean(uint32_t guitarOut, uint32_t dcBias);
const uint32_t getCleanLevelValue(void);
uint32_t* getCleanLevel(void);

#endif /* INC_CLEAN_H_ */
