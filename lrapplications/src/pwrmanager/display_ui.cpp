/*
 * display_ui.cpp
 *
 *  Created on: 22.07.2018
 *      Author: Andreas
 */
#include <stdint.h>

#include "common.h"
#include "hwconfig.h"
#include "display_ui.h"

#include "oledgfx/Adafruit_GFX.h"
#include "ssd1306/Adafruit_SSD1306.h"

#ifdef USE_I2C_DISPLAY
	Adafruit_SSD1306 display(OLED_RESET_PIN);
#endif

/**
 *
 * @return
 */
int displayInitialize()
{
#ifdef USE_I2C_DISPLAY
	// initialize with the I2C addr 0x3C
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	display.clearDisplay();

	// set text color
	display.setTextColor(WHITE);
	// set text size
	display.setTextSize(1);
	// set text cursor position
	display.setCursor(1,0);
#endif

	return 0;
}

/**
 *
 * @return
 */
void displayShowStartupMessage()
{
#ifdef USE_I2C_DISPLAY
	display.clearDisplay();
	display.println(F("J2P Bot - PwrMgr Starting..."));
	display.display();
#endif
}

/**
 *
 */
void displayShowPowerControlStartMessage()
{
#ifdef USE_I2C_DISPLAY
	display.clearDisplay();
	display.println(F("Activating Ouputs..."));
	display.display();
#endif
}

/**
 *
 * @param voltMotor
 * @param voltElectronic
 * @param currentMotor
 * @param currentElectronic
 */
void displayShowMeasurementValues(float voltMotor, float voltElectronic, float currentMotor, float currentElectronic)
{
#ifdef USE_I2C_DISPLAY
	display.clearDisplay();

	display.setCursor(0, 0);
	display.print(F("M [V]: "));
	display.print(voltMotor, 4);

	display.setCursor(0, 8*1);
	display.print(F("E [V]: "));
	display.print(voltElectronic, 4);

	display.setCursor(0, 8*2);
	display.print(F("M [A]: "));
	display.print(currentMotor, 4);

	display.setCursor(0, 8*3);
	display.print(F("E [A]: "));
	display.print(currentElectronic, 4);

	display.display();
#else
	// Use the serial display only of debug messages are deactivated. Otherwiese the
	// clear screen and goto home commands destroy the debug messages
	#if defined(SHOW_MEASUREMENT_SERIAL) && !defined(PWRMGR_DEBUG)
		Serial.write(27);       // ESC command
		Serial.print("[2J");    // clear screen command
		Serial.write(27);
		Serial.print("[H");     // cursor to home command

		Serial.print(F("[powerManager]: Motor [V]: "));
		Serial.println(voltMotor, 4);
		Serial.print(F("[powerManager]: Elec. [V]: "));
		Serial.println(voltElectronic, 4);
		Serial.print(F("[powerManager]: Motor [A]: "));
		Serial.println(currentMotor, 4);
		Serial.print(F("[powerManager]: Elec. [A]: "));
		Serial.println(currentElectronic, 4);
	#endif
#endif
}

/**
 *
 * @return
 */
int indicatorInitialize()
{
    // Set the Buzzer pin to output
	pinMode(BUZZER_PIN, OUTPUT);

	// Set the LED pins to output
	pinMode(LED_MAIN_PIN, OUTPUT);
	pinMode(LED_ELEC_OK_PIN, OUTPUT);
	pinMode(LED_ELEC_NOK_PIN, OUTPUT);
	pinMode(LED_MOTOR_OK_PIN, OUTPUT);
	pinMode(LED_MOTOR_NOK_PIN, OUTPUT);

	// Set the button pins to input with pullup
	pinMode(BUTTON_MAIN_PIN, INPUT_PULLUP);
	pinMode(BUTTON_START1_PIN, INPUT_PULLUP);
	pinMode(BUTTON_START2_PIN, INPUT_PULLUP);

	return 0;
}

/**
 *
 */
void showElectronicStatus(int16_t status)
{
    if (status == STATUS_OK)
    {
        digitalWrite(LED_ELEC_NOK_PIN, LOW);
        digitalWrite(LED_ELEC_OK_PIN, HIGH);
    }
    else if( status == STATUS_NOK)
    {
        digitalWrite(LED_ELEC_NOK_PIN, HIGH);
        digitalWrite(LED_ELEC_OK_PIN, LOW);
    }
}

void showMotorStatus(int16_t status)
{
    if (status == STATUS_OK)
    {
        digitalWrite(LED_MOTOR_NOK_PIN, LOW);
        digitalWrite(LED_MOTOR_OK_PIN, HIGH);
    }
    else if( status == STATUS_NOK)
    {
        digitalWrite(LED_MOTOR_NOK_PIN, HIGH);
        digitalWrite(LED_MOTOR_OK_PIN, LOW);
    }
}

/**
 *
 * @param duration
 */
void indicatorBuzz(uint32_t duration)
{
	uint32_t usedDuration = duration;
	if (usedDuration > MAX_BUZZER_DURATION)
	{
		usedDuration = MAX_BUZZER_DURATION;
	}

	for (uint32_t i=0; i<(usedDuration / 2); i++)
	{
		digitalWrite(BUZZER_PIN, HIGH);
		delay(1);
		digitalWrite(BUZZER_PIN, LOW);
		delay(1);
	}
}

/**
 *
 * @param duration
 */
void indicatorLEDBlink(uint32_t duration)
{
	uint32_t usedDuration = duration;
	if (usedDuration > MAX_LED_DURATION)
	{
		usedDuration = MAX_LED_DURATION;
	}

	for (uint32_t i=0; i<(usedDuration / 500); i++)
	{
		digitalWrite(LED_MAIN_PIN, HIGH);
		delay(250);
		digitalWrite(LED_MAIN_PIN, LOW);
		delay(250);
	}
}

/**
 *
 * @param duration
 */
void indicatorSpeedBlink(uint32_t duration)
{
	uint32_t usedDuration = duration;
	if (usedDuration > MAX_LED_DURATION)
	{
		usedDuration = MAX_LED_DURATION;
	}

	for (uint32_t i=0; i<(usedDuration / 200); i++)
	{
		digitalWrite(LED_MAIN_PIN, HIGH);
		delay(100);
		digitalWrite(LED_MAIN_PIN, LOW);
		delay(100);
	}
}

/**
 *
 * @param duration
 */
void indicatorHazzardBlink(uint32_t duration)
{
	uint32_t usedDuration = duration;
	if (usedDuration > MAX_LED_DURATION)
	{
		usedDuration = MAX_LED_DURATION;
	}

	for (uint32_t i=0; i<(usedDuration / 350); i++)
	{
		for (int j=0; j<5; j++)
		{
			digitalWrite(LED_MAIN_PIN, HIGH);
			delay(50);
			digitalWrite(LED_MAIN_PIN, LOW);
			delay(50);
		}

		delay(250);
	}
}

/**
 *
 */
void showMainStatus(int16_t status)
{
    if (status == STATUS_OK)
    {
        digitalWrite(LED_MAIN_PIN, HIGH);
    }
    else if( status == STATUS_NOK)
    {
        digitalWrite(LED_MAIN_PIN, LOW);
    }
}
