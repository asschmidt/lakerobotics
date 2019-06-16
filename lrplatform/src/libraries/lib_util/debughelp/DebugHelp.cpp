/*
 * DebugHelp.cpp
 *
 *  Created on: 21.12.2018
 *      Author: Andreas
 */
#include <Arduino.h>

#include "DebugHelp.h"

/**
 *
 */
unsigned long startRuntimeMeasurement()
{
	return micros();
}

/**
 *
 */
unsigned long stopRuntimeMeasurement()
{
	return micros();
}

/**
 *
 * @param startValue
 * @param stopValue
 */
unsigned long getRuntime(unsigned long startValue, unsigned long stopValue)
{
	return stopValue - startValue;
}

