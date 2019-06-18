/*
 * common.h
 *
 *  Created on: 26.07.2018
 *      Author: Andreas
 */

#ifndef SRC_APP_PWRMANAGER_COMMON_H_
#define SRC_APP_PWRMANAGER_COMMON_H_

/**
 * If defined, the I2C Library for the OLED Display is used
 * This library uses > 8kB of Flash and ~750 Byte of RAM
 */
//#define USE_I2C_DISPLAY

/**
 * If defined, the measurement values for voltage and current are displayed
 * on the serial console instead of the OLED display. This only works if
 * USE_I2C_DISPLAY is not defined
 */
#define SHOW_MEASUREMENT_SERIAL

/**
 * If defined, Debug messages are displayed
 */
//#define PWRMGR_DEBUG


/**
 *
 */
//#define USE_DATA_HANDLER

#define POWER_MANAGER_LOOP_CYCLE		100		// ms for the Run-Loop Cycle of the Power Manager
#define POWER_MANAGER_CAN_CYCLE			250		// ms for the CAN cycle to transmit CAN messages
#define POWER_MANAGER_DISPLAY_CYCLE		1000	// ms for the Display cycle to update the display
#define POWER_MANAGER_MEASUREMENT_CYCLE	100     // ms for the Measurement Cycle

#define STATUS_OK       0
#define STATUS_NOK      1

#endif /* SRC_APP_PWRMANAGER_COMMON_H_ */
