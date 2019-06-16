/*
 * remotectrl.h
 *
 *  Created on: 27.07.2018
 *      Author: Andreas
 */

#ifndef SRC_APP_PWRMANAGER_REMOTECTRL_H_
#define SRC_APP_PWRMANAGER_REMOTECTRL_H_

/*
 * NEC IR Codes for IR Remote Control from ELEGOO
 */
#define REMOTE_CTRL_POWER 		0xFFA25D
#define REMOTE_CTRL_FUNC		0xFFE21D
#define REMOTE_CTRL_VOL_INC		0xFF629D
#define REMOTE_CTRL_FAST_BACK	0xFF22DD
#define REMOTE_CTRL_PAUSE		0xFF02FD
#define REMOTE_CTRL_FAST_FORW	0xFFC23D
#define REMOTE_CTRL_DOWN		0xFFE01F
#define REMOTE_CTRL_VOL_DEC		0xFFA857
#define REMOTE_CTRL_UP			0xFF906F
#define REMOTE_CTRL_EQ			0xFF9867
#define REMOTE_CTRL_ST			0xFFB04F
#define REMOTE_CTRL_NUM_0		0xFF6897
#define REMOTE_CTRL_NUM_1		0xFF30CF
#define REMOTE_CTRL_NUM_2		0xFF18E7
#define REMOTE_CTRL_NUM_3		0xFF7A85
#define REMOTE_CTRL_NUM_4 		0xFF10EF
#define REMOTE_CTRL_NUM_5		0xFF38C7
#define REMOTE_CTRL_NUM_6		0xFF5AA5
#define REMOTE_CTRL_NUM_7		0xFF42BD
#define REMOTE_CTRL_NUM_8		0xFF4AB5
#define REMOTE_CTRL_NUM_9		0xFF52AD
#define REMOTE_CTRL_REPEAT		0xFFFFFFFF

/*
 * IR Remote Commands evaluated by the power manager
 */
#define REMOTE_CTRL_CMD_UNKNOWN			0
#define REMOTE_CTRL_CMD_POWER			1
#define REMOTE_CTRL_CMD_POWER_MOTOR		2
#define REMOTE_CTRL_CMD_POWER_E1		3
#define REMOTE_CTRL_CMD_POWER_E2		4
#define REMOTE_CTRL_CMD_POWER_E3		5
#define REMOTE_CTRL_CMD_POWER_E_ALL		6

extern void remoteCtrlInitialize();
extern int remoteCtrlProcessCommands();
extern void remoteCtrlClearCommands();
extern int remoteCtrlGetNextCommand();

#endif /* SRC_APP_PWRMANAGER_REMOTECTRL_H_ */
