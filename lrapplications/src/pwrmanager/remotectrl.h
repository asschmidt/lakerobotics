/*
 * remotectrl.h
 *
 *  Created on: 27.07.2018
 *      Author: Andreas
 */

#ifndef SRC_APP_PWRMANAGER_REMOTECTRL_H_
#define SRC_APP_PWRMANAGER_REMOTECTRL_H_

/*
 * IR Remote Commands evaluated by the power manager
 */
#define REMOTE_CTRL_CMD_UNKNOWN			0
#define REMOTE_CTRL_CMD_POWER			1

#define REMOTE_CTRL_CMD_POWER_E1		3
#define REMOTE_CTRL_CMD_POWER_E2		4
#define REMOTE_CTRL_CMD_POWER_E3		5
#define REMOTE_CTRL_CMD_POWER_E4        5
#define REMOTE_CTRL_CMD_POWER_E_ALL		6

extern void remoteCtrlInitialize();
extern int remoteCtrlProcessCommands();
extern void remoteCtrlClearCommands();
extern int remoteCtrlGetNextCommand();

#endif /* SRC_APP_PWRMANAGER_REMOTECTRL_H_ */
