/*
 * pwrcontrol.cpp
 *
 *  Created on: 26.07.2018
 *      Author: Andreas
 */
#include <Arduino.h>

#include "common.h"
#include "hwconfig.h"
#include "pwrcontrol.h"

/**
 *
 */
void powerCtrlInitialize()
{
	// Set the output values to "HIGH" before switching to output mode.
	// This ensures that the relay channels, which are inverted (LOW switches the relay),
	// will not be activated as soon as the output mode is set
	digitalWrite(POWER_MOTOR_CHANNEL_PIN, HIGH);
	digitalWrite(POWER_ELECTRONIC_CHANNEL1_PIN, HIGH);
	digitalWrite(POWER_ELECTRONIC_CHANNEL2_PIN, HIGH);
	digitalWrite(POWER_ELECTRONIC_CHANNEL3_PIN, HIGH);

	pinMode(POWER_MOTOR_CHANNEL_PIN, OUTPUT);
	pinMode(POWER_ELECTRONIC_CHANNEL1_PIN, OUTPUT);
	pinMode(POWER_ELECTRONIC_CHANNEL2_PIN, OUTPUT);
	pinMode(POWER_ELECTRONIC_CHANNEL3_PIN, OUTPUT);
}

/**
 *
 */
void powerCtrlActivateMotor()
{
	digitalWrite(POWER_MOTOR_CHANNEL_PIN, LOW);
}

/**
 *
 */
void powerCtrlDeactivateMotor()
{
	digitalWrite(POWER_MOTOR_CHANNEL_PIN, HIGH);
}

/**
 *
 * @param channel
 */
void powerCtrlActivateElectronics(int16_t channel)
{
	digitalWrite(channel, LOW);
}

/**
 *
 * @param channel
 */
void powerCtrlDeactivateElectronics(int16_t channel)
{
	digitalWrite(channel, HIGH);
}
