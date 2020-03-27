/*
 * measurement.cpp
 *
 *  Created on: 26.03.2020
 *      Author: avsch
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "hal/adc.h"

#include "errorcodes.h"
#include "measurement.h"

static uint32_t gADC_DMA_Buffer[MAX_ADC_CHANNELS];

/**
 *
 * @return
 */
int32_t measurementInitializeADC()
{
    HAL_ADC_Stop(&hadc1);
    HAL_ADCEx_Calibration_Start(&hadc1);

    HAL_ADC_Start_DMA(&hadc1, gADC_DMA_Buffer, MAX_ADC_CHANNELS);

    return ERR_OK;
}

/**
 *
 * @param pValue10
 * @param pValue11
 * @param pValue12
 * @param pValue13
 * @return
 */
int32_t measurementReadADCValues(ADCRawValues* pValues)
{
    pValues->analogM2 = gADC_DMA_Buffer[0];
    pValues->analogM1 = gADC_DMA_Buffer[1];
    pValues->analogIN1 = gADC_DMA_Buffer[2];
    pValues->analogIN2 = gADC_DMA_Buffer[3];
    pValues->analogTempSens = gADC_DMA_Buffer[4];

    pValues->voltageM2 = pValues->analogM2 * MICROVOLT_PER_DIGIT;
    pValues->voltageM1 = pValues->analogM1 * MICROVOLT_PER_DIGIT;
    pValues->voltageIN1 = pValues->analogIN1 * MICROVOLT_PER_DIGIT;
    pValues->voltageIN2 = pValues->analogIN2 * MICROVOLT_PER_DIGIT;
    pValues->voltageTempSens = pValues->analogTempSens * MICROVOLT_PER_DIGIT;

    return ERR_OK;
}

/**
 * Calculates the internal temperature based on the ADC temparature sensor
 * with a scaling of 100.
 * Return Ambient Temperature in 1/100 °C
 * @param pValue
 * @return
 */
int32_t measurementGetInternalTemperature(ADCRawValues* pValues)
{
    int32_t temperature = (((TEMP_SENSOR_V25 - pValues->voltageTempSens) * 100) / TEMP_SENSOR_AVG_SLOPE) + 2500;

    return temperature;
}
