/*
 * measurement.h
 *
 *  Created on: 26.03.2020
 *      Author: avsch
 */

#ifndef LRAPPLICATIONS_SRC_ENGINECTRL_MEASUREMENT_H_
#define LRAPPLICATIONS_SRC_ENGINECTRL_MEASUREMENT_H_

#include <stdint.h>

#define MAX_ADC_CHANNELS        5                   // Number of ADC Channels for the conversion in a regular group
#define MICROVOLT_PER_DIGIT     (3300000/4096)      // Microvolt per Digit
#define TEMP_SENSOR_V25         1430000             // Voltage of the Sensor at 25°C in Microvolt
#define TEMP_SENSOR_AVG_SLOPE   4300                // Voltage of the average slope (µV/°C) in microvolt


typedef struct _ADCRawValues
{
        uint32_t analogM2;          // ADC Channel 10 - PC0
        uint32_t analogM1;          // ADC Channel 11 - PC1
        uint32_t analogIN1;         // ADC Channel 12 - PC2
        uint32_t analogIN2;         // ADC Channel 13 - PC3
        uint32_t analogTempSens;    // Internal Temp Sensor Channel

        int32_t voltageM2;          // Voltage of Channel 10 in µV
        int32_t voltageM1;          // Voltage of Channel 11 in µV
        int32_t voltageIN1;         // Voltage of Channel 12 in µV
        int32_t voltageIN2;         // Voltage of Channel 13 in µV
        int32_t voltageTempSens;    // Voltage of Internal Temp Sensor channel in µV

} ADCRawValues;

extern int32_t measurementInitializeADC();
extern int32_t measurementReadADCValues(ADCRawValues* pValues);
extern int32_t measurementGetInternalTemperature(ADCRawValues* pValue);

#endif /* LRAPPLICATIONS_SRC_ENGINECTRL_MEASUREMENT_H_ */
