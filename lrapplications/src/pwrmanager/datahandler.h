/*
 * datahandler.h
 *
 *  Created on: 18.12.2018
 *      Author: Andreas
 */

#ifndef SRC_APP_PWRMANAGER_DATAHANDLER_H_
#define SRC_APP_PWRMANAGER_DATAHANDLER_H_

#include "datacollect/DataCollector.h"

#define MAX_DATA_ITEMS				10

#define DATA_ITEM_VOLTAGE_ELEC		0	// 16 Bit
#define DATA_ITEM_VOLTAGE_MOTOR		1	// 16 Bit
#define DATA_ITEM_CURRENT_ELEC		2	// 16 Bit
#define DATA_ITEM_CURRENT_MOTOR		3	// 16 Bit
#define DATA_ITEM_CAN_TASK			4	// 32 Bit
#define DATA_ITEM_MEASUREMENT_TASK	6	// 32 Bit
#define DATA_ITEM_PWRMGR_TASK		8	// 32 Bit

extern DataCollector<MAX_DATA_ITEMS>* dataGetCollector();

#endif /* SRC_APP_PWRMANAGER_DATAHANDLER_H_ */
