/*
 * remotectrl.h
 *
 *  Created on: 27.07.2018
 *      Author: Andreas
 */

#ifndef SRC_APP_PWRMANAGER_REMOTECTRL_H_
#define SRC_APP_PWRMANAGER_REMOTECTRL_H_

#include "gen/Node_Pwr_CAN.h"

/*
 * IR Remote Commands evaluated by the power manager
 */
#define REMOTE_CTRL_CMD_UNKNOWN			0
#define REMOTE_CTRL_CMD_POWER			1

#define REMOTE_CTRL_CMD_POWER_E1		2
#define REMOTE_CTRL_CMD_POWER_E2		3
#define REMOTE_CTRL_CMD_POWER_E3		4
#define REMOTE_CTRL_CMD_POWER_E4        5
#define REMOTE_CTRL_CMD_POWER_E_ALL		6

#define REMOTE_CTRL_CMD_POWER_E1_OFF    10
#define REMOTE_CTRL_CMD_POWER_E2_OFF    11
#define REMOTE_CTRL_CMD_POWER_E3_OFF    12
#define REMOTE_CTRL_CMD_POWER_E4_OFF    13

typedef struct _RemoteCtrl_CAN_PowerControl
{
    bool messageValid;
    Msg_Power_Control CAN_PowerControlMsg;
} RemoteCtrl_CAN_PowerControl;

extern void remoteCtrlInitialize();
extern int remoteCtrlProcessCommands();
extern void remoteCtrlClearCommands();
extern int remoteCtrlGetNextCommand();

extern RemoteCtrl_CAN_PowerControl* remoteCtrlGetMsgPowerControl();

#endif /* SRC_APP_PWRMANAGER_REMOTECTRL_H_ */
