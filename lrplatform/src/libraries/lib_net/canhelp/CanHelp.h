/*
 * DebugHelp.h
 *
 *  Created on: 21.12.2018
 *      Author: Andreas
 */

#ifndef SRC_LIBRARIES_CANHELP_CANHELP_H_
#define SRC_LIBRARIES_CANHELP_CANHELP_H_

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


extern int canTransmitValues(MCP2515* pCanController, canid_t canID, int value1, int value2);

#endif /* SRC_LIBRARIES_CANHELP_CANHELP_H_ */
