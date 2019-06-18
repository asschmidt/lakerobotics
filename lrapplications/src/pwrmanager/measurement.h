/*
 * measurement.h
 *
 *  Created on: 22.07.2018
 *      Author: Andreas
 */

#ifndef SRC_APP_PWRMANAGER_MEASUREMENT_H_
#define SRC_APP_PWRMANAGER_MEASUREMENT_H_

#include "ads1x15/Adafruit_ADS1015.h"

/*
 * Measurement Types
 */
#define VOLTAGE_MOTOR		1
#define VOLTAGE_ELECTRONIC	2

#define CURRENT_MOTOR		1
#define CURRENT_ELECTRONIC	2

/*
 * Constant for ADC millivolt per digit
 * Gain value of ADC per default set to +/- 6,144 volts ==> 32767 = 6,144V
 * ==> 6,144 / 32767 = 0,1875 mV/bit
 */
const float ADC_MAX_MILLIVOLT_PER_DIGIT	= 0.1875;

/*
 * Constant for current sensor (ACS712 5A) for voltage per ampere
 * according datasheet 186mV per Ampere
 */
const float CURRENT_SENSOR_VOLT_PER_AMPERE = 0.185;

/*
 * Constant for zero ampere. Typically this is for ACS712 5A a voltage of 2,5V
 */
const float CURRENT_SENSOR_ZERO_VALUE = 2.5;

/*
 * For voltage measurement of motor a voltage divider is used
 *
 * Ua / Ue = R2 / (R1 + R2)
 * ==> Ue = Ua / (R2 / (R1 + R2))
 *
 * Currently R1 = 14610 Ohm and R2 = 4660 Ohm
 * ==> r = 0,24182667358588479501816294758692
 */
const float VOLTAGE_MOTOR_DIVIDER_FACTOR = 0.241826;

/*
 * For voltage measurement of electronics a voltage divider is used
 *
 * Ua / Ue = R2 / (R1 + R2)
 * ==> Ue = Ua / (R2 / (R1 + R2))
 *
 * Original
 * Currently R1 = 8485 Ohm and R2 = 3114 Ohm
 * ==> r = 0,26847141994999568928355892749375
 *
 * Based on measurement
 * Currently R1 = 9668 Ohm and R2 = 3114 Ohm
 * ==> r = 0,24362384603348458770145517133469
 */
const float VOLTAGE_ELECTRONICS_DIVIDER_FACTOR = 0.243623;

/*
 * Max voltage for ADC measurement (only for PGA relevant, not for analog input!!)
 */
const float MAX_ADC_VOLTAGE = 6.144;

/*
 * Structure for measurement relevant parameter
 */
typedef struct _MEASUREMENT_PARAMETER
{
	float maxADCVoltage;		// Max ADC voltage (used for PGA)
	float adcVDD;				// Supply voltage of ADC
	float adcmVperDigit;		// mV per Digit
	adsGain_t adcGain;			// Current ADC Gain
} MEASUREMENT_PARAMETER;

/*
 * Structure for the measurement values acquired by this module
 */
typedef struct _MEASUREMENT_VALUES
{
	float voltageElectronics;	// Voltage of the electronics supply in [V]
	float voltageMotor;			// Voltage of the motor supply in [V]
	float currentElectronics;	// Current of the electronics supply in [A]
	float currentMotor;			// Current of the motor supply in [A]
} MEASUREMENT_VALUES;

extern int16_t measurementInitialize(void);
extern int16_t measurementPerformMeasurement(void);
extern MEASUREMENT_VALUES* measurementGetValues(void);

#endif /* SRC_APP_PWRMANAGER_MEASUREMENT_H_ */
