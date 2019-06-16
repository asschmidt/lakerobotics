/*
 * display_ui.h
 *
 *  Created on: 22.07.2018
 *      Author: Andreas
 */

#ifndef SRC_APP_PWRMANAGER_DISPLAY_UI_H_
#define SRC_APP_PWRMANAGER_DISPLAY_UI_H_

#define MAX_BUZZER_DURATION				2000
#define MAX_LED_DURATION				10000

extern int displayInitialize();
extern void displayShowStartupMessage();
extern void displayShowPowerControlStartMessage();
extern void displayShowMeasurementValues(float voltMotor, float voltElectronic, float currentMotor, float currentElectronic);

extern int indicatorInitialize();
extern void indicatorBuzz(unsigned long duration);
extern void indicatorLEDBlink(unsigned long duration);
extern void indicatorHazzardBlink(unsigned long duration);
extern void indicatorSpeedBlink(unsigned long duration);

#endif /* SRC_APP_PWRMANAGER_DISPLAY_UI_H_ */
