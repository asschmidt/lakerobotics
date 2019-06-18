/*
 * canhandler.h
 *
 *  Created on: 22.07.2018
 *      Author: Andreas
 */

#ifndef SRC_APP_PWRMANAGER_CANHANDLER_H_
#define SRC_APP_PWRMANAGER_CANHANDLER_H_

#include "mcp2515/mcp2515.h"

extern int canHandlerInitialize(const CAN_SPEED speed);

extern int canHandlerTransmitMeasurementValues(canid_t canID, int16_t value1, int16_t value2);
extern int canHandlerProcessReceiveMessages();

#endif /* SRC_APP_PWRMANAGER_CANHANDLER_H_ */
