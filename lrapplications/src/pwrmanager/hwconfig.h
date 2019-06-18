/*
 * hwconfig.h
 *
 *  Created on: 27.07.2018
 *      Author: Andreas
 */

#ifndef SRC_APP_PWRMANAGER_HWCONFIG_H_
#define SRC_APP_PWRMANAGER_HWCONFIG_H_

/*
 * Constant for GPIO pins used for the CAN-Controller
 */
#define CAN_CONTROLLER_INT_PIN			3
#define CAN_CONTROLLER_CS_PIN			10


/*
 * Constant for GPIO pins used to control the relays for the power channels
 */

#define POWER_ELECTRONIC_CHANNEL1_PIN	6
#define POWER_ELECTRONIC_CHANNEL2_PIN	7
#define POWER_ELECTRONIC_CHANNEL3_PIN	8
#define POWER_ELECTRONIC_CHANNEL4_PIN   9

/*
 * Constant for GPIO pins used for UI (LED, Buzzer and Buttonts)
 */
#define BUZZER_PIN						4

#define LED_MAIN_PIN                    5

#define LED_MOTOR_OK_PIN				A3
#define LED_MOTOR_NOK_PIN               A0
#define LED_ELEC_OK_PIN                 A2
#define LED_ELEC_NOK_PIN                A1

#define BUTTON_MAIN_PIN                 0
#define BUTTON_START1_PIN               2
#define BUTTON_START2_PIN               1

/*
 * Configuration of analog channels
 *
 * ADC0: Motor Current
 * ADC1: Electronics Current
 * ADC2: Motor Voltage
 * ADC3: Electronics Voltage
 *
 */
#define VOLTAGE_MOTOR_ADC_CHANNEL		0
#define CURRENT_MOTOR_ADC_CHANNEL		1
#define VOLTAGE_ELECTRONIC_ADC_CHANNEL	2
#define CURRENT_ELECTRONIC_ADC_CHANNEL	3

#endif /* SRC_APP_PWRMANAGER_HWCONFIG_H_ */
