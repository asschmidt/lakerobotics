/*
 * DebugHelp.h
 *
 *  Created on: 21.12.2018
 *      Author: Andreas
 */

#ifndef SRC_LIBRARIES_DEBUGHELP_DEBUGHELP_H_
#define SRC_LIBRARIES_DEBUGHELP_DEBUGHELP_H_



extern unsigned long startRuntimeMeasurement();
extern unsigned long stopRuntimeMeasurement();
extern unsigned long getRuntime(unsigned long startValue, unsigned long stopValue);

#endif /* SRC_LIBRARIES_DEBUGHELP_DEBUGHELP_H_ */
