/*
 * display_ui.cpp
 *
 *  Created on: 22.07.2018
 *      Author: Andreas
 */
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
	pinMode(BUZZER_PIN, OUTPUT);
	pinMode(LED_PIN, OUTPUT);

	return 0;
}

/**
 *
 * @param duration
 */
void indicatorBuzz(unsigned long duration)
{
	unsigned long usedDuration = duration;
	if (usedDuration > MAX_BUZZER_DURATION)
	{
		usedDuration = MAX_BUZZER_DURATION;
	}

	for (unsigned long i=0; i<(usedDuration / 2); i++)
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
void indicatorLEDBlink(unsigned long duration)
{
	unsigned long usedDuration = duration;
	if (usedDuration > MAX_LED_DURATION)
	{
		usedDuration = MAX_LED_DURATION;
	}

	for (unsigned long i=0; i<(usedDuration / 500); i++)
	{
		digitalWrite(LED_PIN, HIGH);
		delay(250);
		digitalWrite(LED_PIN, LOW);
		delay(250);
	}
}

/**
 *
 * @param duration
 */
void indicatorSpeedBlink(unsigned long duration)
{
	unsigned long usedDuration = duration;
	if (usedDuration > MAX_LED_DURATION)
	{
		usedDuration = MAX_LED_DURATION;
	}

	for (unsigned long i=0; i<(usedDuration / 200); i++)
	{
		digitalWrite(LED_PIN, HIGH);
		delay(100);
		digitalWrite(LED_PIN, LOW);
		delay(100);
	}
}

/**
 *
 * @param duration
 */
void indicatorHazzardBlink(unsigned long duration)
{
	unsigned long usedDuration = duration;
	if (usedDuration > MAX_LED_DURATION)
	{
		usedDuration = MAX_LED_DURATION;
	}

	for (unsigned long i=0; i<(usedDuration / 350); i++)
	{
		for (int j=0; j<5; j++)
		{
			digitalWrite(LED_PIN, HIGH);
			delay(50);
			digitalWrite(LED_PIN, LOW);
			delay(50);
		}

		delay(250);
	}
}
