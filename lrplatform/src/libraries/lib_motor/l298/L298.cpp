/*
 * L298.cpp
 *
 *  Created on: 05.10.2018
 *      Author: Andreas
 */


#include <Arduino.h>

#include "L298.h"

/**
 *
 * @param enaPin
 * @param in1Pin
 * @param in2Pin
 */
L298::L298(int enaPin, int in1Pin, int in2Pin)
{
	enablePin = enaPin;
	input1Pin = in1Pin;
	input2Pin = in2Pin;

	pinMode(enablePin, OUTPUT);
	pinMode(input1Pin, OUTPUT);
	pinMode(input2Pin, OUTPUT);

	setDirection(STOP);
	setMode(NORMAL);
}

/**
 *
 * @param dir
 */
void L298::setInternalDirection(L298_DIRECTION dir)
{
	switch (dir)
	{
		case STOP:
			digitalWrite(input1Pin, LOW);
			digitalWrite(input2Pin, LOW);
			break;

		case FORWARD:
			digitalWrite(input1Pin, HIGH);
			digitalWrite(input2Pin, LOW);
			break;

		case REVERSE:
			digitalWrite(input1Pin, LOW);
			digitalWrite(input2Pin, HIGH);
			break;

		default:
			// In any other case there is no need to change pin settings
			break;
	}
}

/**
 *
 * @param direction
 */
void L298::setDirection(L298_DIRECTION dir)
{
	direction = dir;
	setInternalDirection(direction);
}

/**
 *
 * @return
 */
L298_DIRECTION L298::getDirection()
{
	return direction;
}

/**
 *
 * @param m
 */
void L298::setMode(L298_MODE m)
{
	mode = m;
}

/**
 *
 * @return
 */
L298_MODE L298::getMode()
{
	return mode;
}

/**
 *
 * @param speed
 */
void L298::setSpeed(int speed)
{
	if (mode == NORMAL)
	{
		if (speed >= 0 && speed <= 255)
		{
			analogWrite(enablePin, speed);
		}
		else
		{
			analogWrite(enablePin, 0);
		}
	}
	else
	{
		//Serial.println("New Speed");
		int newSpeed = speed;

		if (speed >= -255 && speed < 0)
		{
			//Serial.println("Set Dir: ");

			setDirection(REVERSE);

			//Serial.print("Speedy: ");
			//Serial.println(newSpeed);

			newSpeed = speed * -1;

			//Serial.print("Speedx: ");
			//Serial.println(newSpeed);
		}
		else
		{
			//Serial.println("SetSpeed Go Forward");
			setDirection(FORWARD);
		}

		//Serial.println("Set Speed final");
		analogWrite(enablePin, newSpeed);
	}
}

/**
 *
 */
void L298::stop()
{
	setSpeed(0);
	setDirection(STOP);
}

