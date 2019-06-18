/*
 * pwrcontrol.h
 *
 *  Created on: 26.07.2018
 *      Author: Andreas
 */

#ifndef SRC_APP_PWRMANAGER_PWRCONTROL_H_
#define SRC_APP_PWRMANAGER_PWRCONTROL_H_

extern void powerCtrlInitialize();
extern void powerCtrlActivateMotor();
extern void powerCtrlDeactivateMotor();

extern void powerCtrlActivateElectronics(int16_t channel);
extern void powerCtrlDeactivateElectronics(int16_t channel);

#endif /* SRC_APP_PWRMANAGER_PWRCONTROL_H_ */
