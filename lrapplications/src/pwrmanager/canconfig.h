/*
 * canconfig.h
 *
 *  Created on: 25.08.2018
 *      Author: Andreas
 */

#ifndef SRC_APP_PWRMANAGER_CANCONFIG_H_
#define SRC_APP_PWRMANAGER_CANCONFIG_H_

/*
 * CAN ID Definition
 * Bit 31: Extended Frame Bit
 * Bit 30: Remote Transmission Flag
 * Bit 29: Error Message Flag
 * Bit 28: Broadcast Flag
 * Bit 27-24: Destination Node ID
 * Bit 23-20: Source Node ID
 * Bit 19-0: Message ID
 */
#define MAKE_CAN_ID(srcId, dstId, msgid)		((((unsigned long)(dstId & 0x0F) << 24) | ((unsigned long)(srcId & 0x0F) << 20) | (unsigned long)(msgid & 0x7FFFF)) | CAN_EFF_FLAG)
#define MAKE_BROADCAST_CAN_ID(srcId, msgid)		((unsigned long)(MAKE_CAN_ID(srcId, 0x00, msgid) | (((unsigned long)0x01 << 28))))

#define PWRMANAGER_NODE_ID						0x01

#define PWRMANAGER_TX_MOTOR_VALUES_ID			0x01
#define PWRMANAGER_TX_ELECTRONIC_VALUES_ID		0x02
#define PWRMANAGER_TX_POWER_STATUS_ID			0x03

#define PWRMANAGER_RX_POWER_CTRL_ID				0x01


#endif /* SRC_APP_PWRMANAGER_CANCONFIG_H_ */
