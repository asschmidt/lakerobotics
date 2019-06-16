/*
 * measurement.cpp
 *
 *  Created on: 22.07.2018
 *      Author: Andreas
 */
#include "common.h"
#include "hwconfig.h"
#include "measurement.h"

#include "wire/Wire.h"
#include "ads1x15/Adafruit_ADS1015.h"

static Adafruit_ADS1115 g_ADC;

static MEASUREMENT_PARAMETER g_measurementParams;
static MEASUREMENT_VALUES g_measurementValues;

static void setADCGain(MEASUREMENT_PARAMETER* pParams, adsGain_t gain);
static void setADCGainToZero(MEASUREMENT_PARAMETER* pParams);
static void calibrateADCSupplyVoltage(MEASUREMENT_PARAMETER* pParams);

static float performVoltageMeasurement(int voltageType);
static float performCurrentMeasurement(int currentType);

/**
 *
 * @param pParams
 * @param gain
 */
void setADCGain(MEASUREMENT_PARAMETER* pParams, adsGain_t gain)
{
	pParams->adcGain = gain;

	switch (pParams->adcGain)
	{
		case GAIN_TWOTHIRDS:
			pParams->maxADCVoltage = MAX_ADC_VOLTAGE;
			pParams->adcmVperDigit = 0.1875;
			break;

		case GAIN_ONE:
			pParams->maxADCVoltage = 4.096;
			pParams->adcmVperDigit = 0.125;
			break;

		case GAIN_TWO:
			pParams->maxADCVoltage = 2.048;
			pParams->adcmVperDigit = 0.0625;
			break;

		case GAIN_FOUR:
			pParams->maxADCVoltage = 1.024;
			pParams->adcmVperDigit = 0.03125;
			break;

		case GAIN_EIGHT:
			pParams->maxADCVoltage = 0.512;
			pParams->adcmVperDigit = 0.01562;
			break;

		case GAIN_SIXTEEN:
			pParams->maxADCVoltage = 0.256;
			pParams->adcmVperDigit = 0.0078125;
			break;

		default:
			pParams->maxADCVoltage = MAX_ADC_VOLTAGE;
	}
}

/**
 *
 */
void setADCGainToZero(MEASUREMENT_PARAMETER* pParams)
{
	setADCGain(pParams, GAIN_TWOTHIRDS);
	g_ADC.setGain(pParams->adcGain);
}

/**
 *
 * @param pParams
 */
void calibrateADCSupplyVoltage(MEASUREMENT_PARAMETER* pParams)
{
	int vddRawValue = analogRead(ADC_VDD_MEASUREMENT_PIN);
	float vddVoltage = vddRawValue * 0.0049;

	pParams->adcVDD = vddVoltage;

#ifdef PWRMGR_DEBUG
	Serial.print(F("[calibrateADCSupplyVoltage]: VDD of ADC: "));
	Serial.println(vddVoltage, 5);
#endif
}

/**
 *
 * @return
 */
int measurementInitialize(void)
{
	g_ADC.begin();

	// Init the parameter with default values
	g_measurementParams.maxADCVoltage = MAX_ADC_VOLTAGE;
	g_measurementParams.adcGain = GAIN_TWOTHIRDS;
	g_measurementParams.adcmVperDigit = ADC_MAX_MILLIVOLT_PER_DIGIT;
	g_measurementParams.adcVDD = 0;

	g_measurementValues.currentElectronics = 0.0;
	g_measurementValues.currentMotor = 0.0;
	g_measurementValues.voltageElectronics = 0.0;
	g_measurementValues.voltageMotor = 0.0;

	setADCGainToZero(&g_measurementParams);
	calibrateADCSupplyVoltage(&g_measurementParams);

	return 0;
}

/**
 *
 * @param voltageType
 * @return
 */
float performVoltageMeasurement(int voltageType)
{
	int16_t adcValue = 0;
	float rawVoltageValue = 0.0;
	float voltageValue = 0.0;

	if (voltageType == VOLTAGE_MOTOR)
	{
		adcValue = g_ADC.readADC_SingleEnded(VOLTAGE_MOTOR_ADC_CHANNEL);

		// Calculate the measured value into unit Volts [V]
		rawVoltageValue = (adcValue * g_measurementParams.adcmVperDigit) / 1000;

		// Calculate the original voltage based on voltage divider
		voltageValue = rawVoltageValue / VOLTAGE_MOTOR_DIVIDER_FACTOR;
	}
	else if (voltageType == VOLTAGE_ELECTRONIC)
	{
		adcValue = g_ADC.readADC_SingleEnded(VOLTAGE_ELECTRONIC_ADC_CHANNEL);

		// Calculate the measured value into unit Volts [V]
		rawVoltageValue = (adcValue * g_measurementParams.adcmVperDigit) / 1000;

		// Calculate the original voltage based on voltage divider
		voltageValue = rawVoltageValue / VOLTAGE_ELECTRONICS_DIVIDER_FACTOR;
	}

#ifdef PWRMGR_DEBUG
	if (voltageType == VOLTAGE_MOTOR)
	{
		Serial.print(F("[performVoltageMeasurement]: Motor Voltage Raw [V]: ")); Serial.println(rawVoltageValue, 3);
		Serial.print(F("[performVoltageMeasurement]: Motor Voltage [V]: ")); Serial.println(voltageValue, 4);
	}
	else if (voltageType == VOLTAGE_ELECTRONIC)
	{
		Serial.print(F("[performVoltageMeasurement]: Elec. Voltage Raw [V]: ")); Serial.println(rawVoltageValue, 3);
		Serial.print(F("[performVoltageMeasurement]: Elec. Voltage [V]: ")); Serial.println(voltageValue, 4);
	}
#endif

	return voltageValue;
}

/**
 *
 * @param currentType
 * @return
 */
float performCurrentMeasurement(int currentType)
{
	int16_t adcValue = 0;

	if (currentType == CURRENT_MOTOR)
	{
		adcValue = g_ADC.readADC_SingleEnded(CURRENT_MOTOR_ADC_CHANNEL);
	}
	else if (currentType == CURRENT_ELECTRONIC)
	{
		adcValue = g_ADC.readADC_SingleEnded(CURRENT_ELECTRONIC_ADC_CHANNEL);
	}

	// Calculate the measured value into unit Volts [V]
	float voltageValue = 0.0;
	voltageValue = (adcValue * g_measurementParams.adcmVperDigit) / 1000;

	// Calculate the current based on measured voltage
	// voltage - 2,5V zero point
	float currentValue = 0.0;
	currentValue = (voltageValue - (g_measurementParams.adcVDD * 0.5)) / CURRENT_SENSOR_VOLT_PER_AMPERE;

#ifdef PWRMGR_DEBUG
	if (currentType == CURRENT_MOTOR)
	{
		Serial.print(F("[performCurrentMeasurement]: Motor Current Raw [V]: ")); Serial.println(voltageValue, 3);
		Serial.print(F("[performCurrentMeasurement]: Motor Current [A]: ")); Serial.println(currentValue, 3);
	}
	else if (currentType == CURRENT_ELECTRONIC)
	{
		Serial.print(F("[performCurrentMeasurement]: Elec. Current Raw [V]: ")); Serial.println(voltageValue, 3);
		Serial.print(F("[performCurrentMeasurement]: Elec. Current [A]: ")); Serial.println(currentValue, 3);
	}
#endif

	return currentValue;
}

/**
 *
 * @return
 */
int measurementPerformMeasurement(void)
{
	// Accquire the measurement values for voltage and current
	g_measurementValues.voltageElectronics = performVoltageMeasurement(VOLTAGE_ELECTRONIC);
	g_measurementValues.voltageMotor = performVoltageMeasurement(VOLTAGE_MOTOR);
    g_measurementValues.currentElectronics = performCurrentMeasurement(CURRENT_ELECTRONIC);
	g_measurementValues.currentMotor = performCurrentMeasurement(CURRENT_MOTOR);

	return 0;
}

/**
 *
 * @return
 */
MEASUREMENT_VALUES* measurementGetValues()
{
	return &g_measurementValues;
}
