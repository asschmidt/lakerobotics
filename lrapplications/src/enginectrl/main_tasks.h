/*
 * main_tasks.h
 *
 *  Created on: 28.03.2020
 *      Author: avsch
 */

#ifndef LRAPPLICATIONS_SRC_ENGINECTRL_MAIN_TASKS_H_
#define LRAPPLICATIONS_SRC_ENGINECTRL_MAIN_TASKS_H_

#define CYCLE_TIME_MOTOR_CONTROL_TASK           10
#define CYCLE_TIME_CANHANDLER_TASK              50
#define CYCLE_TIME_ADC_ACCQUISITION_TASK        50

void taskCANHandler(void *pvParameters);
void taskADCAccquire(void *pvParameters);
void taskMotorControl(void *pvParameters);

#endif /* LRAPPLICATIONS_SRC_ENGINECTRL_MAIN_TASKS_H_ */
