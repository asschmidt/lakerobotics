/*
 * pwrmanager.h
 *
 *  Created on: 27.07.2018
 *      Author: Andreas
 */

#ifndef SRC_APP_PWRMANAGER_PWRMANAGER_H_
#define SRC_APP_PWRMANAGER_PWRMANAGER_H_

#define POWER_STARTUP_STATE_DELAY	2000	// ms to wait befor activating the power stages for electronics

#define POWER_SHUTDOWN_DELAY		1000	// ms to wait before shutdown phase is initiated
#define POWER_SHUTDOWN_STAGE_DELAY	2000	// ms to wait after shutdown of each power stage

/**
 * Define the different states for the power manager
 */
#define PWRM_MODE_INIT			0	// Initialization
#define PWRM_MODE_PRE_POWER		1	// Before activating the power outputs
#define PWRM_MODE_POWER_START	2	// Activating the power outputs
#define PWRM_MODE_RUN			3	// Normal operation mode
#define PWRM_MODE_FAILURE		4	// Failure mode in case of detected malfaction
#define PWRM_MODE_SHUTDOWN		5	// Stop, all output deactivated

typedef struct _POWER_OUTPUT_STATES
{
	uint16_t stateElectronic1Power 	: 1;
	uint16_t stateElectronic2Power 	: 1;
	uint16_t stateElectronic3Power 	: 1;
	uint16_t stateElectronic4Power  : 1;
} POWER_OUPUT_STATES;

typedef struct _PWRM_STATE_MACHINE
{
    int16_t pwrManagerMode;
    int16_t pwrManagerLastMode;

    int16_t pwrManagerRemoteCommand;

	POWER_OUPUT_STATES pwrManagerOutputStates;
} PWR_STATE_MACHINE;


void powerManagerInitialize(PWR_STATE_MACHINE* pPwrManager);
int16_t powerManagerSwitchMode(PWR_STATE_MACHINE* pPwrManager, int16_t newMode);
int16_t powerManagerRunStateMachine(PWR_STATE_MACHINE* pPwrManager);

#endif /* SRC_APP_PWRMANAGER_PWRMANAGER_H_ */
