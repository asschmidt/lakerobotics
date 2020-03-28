/*
 * hwtest_tasks.h
 *
 *  Created on: 28.03.2020
 *      Author: avsch
 */

#ifndef LRAPPLICATIONS_SRC_HWTEST_TASKS_H_
#define LRAPPLICATIONS_SRC_HWTEST_TASKS_H_


void taskPWMMotorTest(void *pvParameters);
void taskEncoderTest(void *pvParameters);
void taskAnalogTest(void *pvParameters);
void taskCANHandlerTest(void *pvParameters);


#endif /* LRAPPLICATIONS_SRC_HWTEST_TASKS_H_ */
