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
extern void indicatorBuzz(uint32_t duration);
extern void indicatorLEDBlink(uint32_t duration);
extern void indicatorHazzardBlink(uint32_t duration);
extern void indicatorSpeedBlink(uint32_t duration);

extern void showMainStatus(int16_t status);
extern void showElectronicStatus(int16_t status);
extern void showMotorStatus(int16_t status);

#endif /* SRC_APP_PWRMANAGER_DISPLAY_UI_H_ */
