/*
 * SimpleEncoder.cpp
 *
 *  Created on: 05.10.2018
 *      Author: Andreas
 */

#include "Arduino.h"

#include "utility/direct_pin_read.h"
#include "SimpleEncoder.h"

SIMPLE_ENCODER_STATE* SimpleEncoder::actualEncoder1 = NULL;
SIMPLE_ENCODER_STATE* SimpleEncoder::actualEncoder2 = NULL;

SIMPLE_ENCODER_STATE SimpleEncoder::encoderState1;
SIMPLE_ENCODER_STATE SimpleEncoder::encoderState2;

/**
 *
 * @param pinA
 * @param pinB
 */
SimpleEncoder::SimpleEncoder(int numberOfCounts1, int pin1A, int pin1B, int numberOfCounts2, int pin2A, int pin2B)
{
	if (pin1A != 0)
	{
		pinMode(pin1A, INPUT_PULLUP);
		pinMode(pin1B, INPUT_PULLUP);

		attachInterrupt(digitalPinToInterrupt(pin1A), handleEncoder1A, RISING);

		SimpleEncoder::encoderState1.numberOfCounts = numberOfCounts1;
		SimpleEncoder::encoderState1.speed = 0;
		SimpleEncoder::encoderState1.position = 0;
		SimpleEncoder::encoderState1.prevTime = 0;
		SimpleEncoder::encoderState1.timestep = 0;

		SimpleEncoder::encoderState1.pin1ARegister = PIN_TO_BASEREG(pin1A);
		SimpleEncoder::encoderState1.pin1ABitmask = PIN_TO_BITMASK(pin1A);
		SimpleEncoder::encoderState1.pin1BRegister = PIN_TO_BASEREG(pin1B);
		SimpleEncoder::encoderState1.pin1BBitmask = PIN_TO_BITMASK(pin1B);

		SimpleEncoder::actualEncoder1 = &SimpleEncoder::encoderState1;
	}

	if (pin2A != 0)
	{
		pinMode(pin2A, INPUT_PULLUP);
		pinMode(pin2B, INPUT_PULLUP);

		attachInterrupt(digitalPinToInterrupt(pin2A), handleEncoder2A, RISING);

		SimpleEncoder::encoderState2.numberOfCounts = numberOfCounts2;
		SimpleEncoder::encoderState2.speed = 0;
		SimpleEncoder::encoderState2.position = 0;
		SimpleEncoder::encoderState2.prevTime = 0;
		SimpleEncoder::encoderState2.timestep = 0;

		SimpleEncoder::encoderState2.pin1ARegister = PIN_TO_BASEREG(pin2A);
		SimpleEncoder::encoderState2.pin1ABitmask = PIN_TO_BITMASK(pin2A);
		SimpleEncoder::encoderState2.pin1BRegister = PIN_TO_BASEREG(pin2B);
		SimpleEncoder::encoderState2.pin1BBitmask = PIN_TO_BITMASK(pin2B);

		SimpleEncoder::actualEncoder2 = &SimpleEncoder::encoderState2;
	}
}

/**
 *
 * @param encoderID
 */
long SimpleEncoder::getPosition(SIMPLE_ENCODER_ID encoderID)
{
	unsigned long position = 0;
	SIMPLE_ENCODER_STATE* pEncoder = NULL;

	switch (encoderID)
	{
		case ENCODER1:
			pEncoder = &SimpleEncoder::encoderState1;
			break;

		case ENCODER2:
			pEncoder = &SimpleEncoder::encoderState2;
			break;
	}

	noInterrupts();
	position = pEncoder->position;
	interrupts();

	return position;
}

/**
 *
 * @param encoderID
 */
unsigned long SimpleEncoder::getSpeed(SIMPLE_ENCODER_ID encoderID, SIMPLE_ENCODER_SPEED_TYPE speedType)
{
	unsigned long speed = 0;
	SIMPLE_ENCODER_STATE* pEncoder = NULL;

	switch (encoderID)
	{
		case ENCODER1:
			pEncoder = &SimpleEncoder::encoderState1;
			break;

		case ENCODER2:
			pEncoder = &SimpleEncoder::encoderState2;
			break;
	}

	unsigned long now = micros();

	noInterrupts();

	if ((now - pEncoder->prevTime) > ENCODER_MAX_TIMESTEP)
	{
		pEncoder->timestep = 0;
	}

	if (pEncoder->timestep != 0)
	{
		if (speedType == SPEED_RPM)
		{
			// Calculate rpm
			//speed = 60 * 1000000 / (pEncoder->numberOfCounts * pEncoder->timestep);
			speed = 60 * ((1000000 / pEncoder->timestep) / pEncoder->numberOfCounts);
		}
		else
		{
			// Calculate round per millisecond
			speed = 0;
		}
	}
	else
	{
		speed = 0;
	}

	interrupts();

	return speed;
}

/**
 *
 */
void SimpleEncoder::handleEncoder1A()
{
	if (SimpleEncoder::actualEncoder1 != NULL)
	{
		handleEncoder(SimpleEncoder::actualEncoder1);
	}
}

/**
 *
 */
void SimpleEncoder::handleEncoder2A()
{
	if (SimpleEncoder::actualEncoder2 != NULL)
	{
		handleEncoder(SimpleEncoder::actualEncoder2);
	}
}

/**
 *
 * @param pEncoder
 */
void SimpleEncoder::handleEncoder(SIMPLE_ENCODER_STATE* pEncoder)
{
	// Speed Handling
	unsigned long now = micros();
	pEncoder->timestep = now - pEncoder->prevTime;
	pEncoder->prevTime = now;

	// Position Handling
	//uint8_t aVal = DIRECT_PIN_READ(pEncoder->pin1ARegister, pEncoder->pin1ABitmask);
	uint8_t bVal = DIRECT_PIN_READ(pEncoder->pin1BRegister, pEncoder->pin1BBitmask);

	if (bVal == 1)
	{
		pEncoder->position++;
	}
	else
	{
		pEncoder->position--;
	}
}
