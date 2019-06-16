/*
 * hwconfig.h
 *
 *  Created on: 27.07.2018
 *      Author: Andreas
 */

#ifndef SRC_APP_PWRMANAGER_HWCONFIG_H_
#define SRC_APP_PWRMANAGER_HWCONFIG_H_

/*
 * Arduino Pin Settings
 */
#define CAN_CONTROLLER_INT_PIN			2
#define CAN_CONTROLLER_CS_PIN			10

/*
 * Constant for GPIO pins used for IR
 */

#define IR_RECEIVER_PIN					9
#define IR_RECEIVER_BLINK_PIN			1

/*
 * Constant for GPIO pins used to control the relays for the power channels
 */

#define POWER_MOTOR_CHANNEL_PIN			7
#define POWER_ELECTRONIC_CHANNEL1_PIN	4
#define POWER_ELECTRONIC_CHANNEL2_PIN	5
#define POWER_ELECTRONIC_CHANNEL3_PIN	6

#define OLED_RESET_PIN 					0  // not used

#define BUZZER_PIN						8
#define LED_PIN							3

#define ADC_VDD_MEASUREMENT_PIN			A0

/*
 * Configuration of analog channels
 *
 * ADC0: Motor Current
 * ADC1: Electronics Current
 * ADC2: Motor Voltage
 * ADC3: Electronics Voltage
 *
 */
#define VOLTAGE_MOTOR_ADC_CHANNEL		2
#define CURRENT_MOTOR_ADC_CHANNEL		0
#define VOLTAGE_ELECTRONIC_ADC_CHANNEL	3
#define CURRENT_ELECTRONIC_ADC_CHANNEL	1

#endif /* SRC_APP_PWRMANAGER_HWCONFIG_H_ */
