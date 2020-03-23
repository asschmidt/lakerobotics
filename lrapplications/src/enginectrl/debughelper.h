/*
 * debughelper.h
 *
 *  Created on: 22.03.2020
 *      Author: avsch
 */

#ifndef LRAPPLICATIONS_SRC_ENGINECTRL_DEBUGHELPER_H_
#define LRAPPLICATIONS_SRC_ENGINECTRL_DEBUGHELPER_H_

#include <stdint.h>

#define MAX_DEBUG_MESSAGE_BUFFER        128

#define DEBUG_UART                      huart2
/*
 * Public Debug Helper API
 */
extern void debugPrint(const char *format, ...);

#endif /* LRAPPLICATIONS_SRC_ENGINECTRL_DEBUGHELPER_H_ */
