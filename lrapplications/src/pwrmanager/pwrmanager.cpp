/*
 * pwrmanager.cpp
 *
 *  Created on: 22.07.2018
 *      Author: Andreas
 */
#include <stdint.h>

#include "common.h"
#include "hwconfig.h"
#include "canconfig.h"

#include "pwrmanager.h"
#include "measurement.h"
#include "pwrcontrol.h"
#include "canhandler.h"
#include "display_ui.h"
#include "remotectrl.h"

static void powerManagerHandlePrePowerMode(PWR_STATE_MACHINE* pPwrManager);
static void powerManagerHandlePowerStartMode(PWR_STATE_MACHINE* pPwrManager);
static void powerManagerHandleRunMode(PWR_STATE_MACHINE* pPwrManager);
static void powerManagerHandleShutdown(PWR_STATE_MACHINE* pPwrManager);
static void powerManagerUpdateUIStatus(PWR_STATE_MACHINE* pPwrManager);
static void powerManagerHandleStageSwitchCommands(PWR_STATE_MACHINE* pPwrManager);

/**
 *
 * @param pPwrManager
 */
void powerManagerInitialize(PWR_STATE_MACHINE* pPwrManager)
{
	pPwrManager->pwrManagerMode = PWRM_MODE_INIT;
}

/**
 *
 * @param pwrManager
 * @param newMode
 * @return
 */
int16_t powerManagerSwitchMode(PWR_STATE_MACHINE* pPwrManager, int16_t newMode)
{
	pPwrManager->pwrManagerLastMode = pPwrManager->pwrManagerMode;
	pPwrManager->pwrManagerMode = newMode;

	return pPwrManager->pwrManagerLastMode;
}

/**
 *
 * @param pPwrManager
 */
void powerManagerHandlePrePowerMode(PWR_STATE_MACHINE* pPwrManager)
{
	if (pPwrManager->pwrManagerRemoteCommand == REMOTE_CTRL_CMD_POWER)
	{
		powerManagerSwitchMode(pPwrManager, PWRM_MODE_POWER_START);
		pPwrManager->pwrManagerRemoteCommand = REMOTE_CTRL_CMD_UNKNOWN;

		#ifdef PWRMGR_DEBUG
			Serial.println(F("Switching to Power Start"));
		#endif

		indicatorLEDBlink(500);
	}
}

/**
 *
 * @param pPwrManager
 */
void powerManagerHandleStageSwitchCommands(PWR_STATE_MACHINE* pPwrManager)
{
    switch (pPwrManager->pwrManagerRemoteCommand)
    {
        case REMOTE_CTRL_CMD_POWER_E1:
            #ifdef PWRMGR_DEBUG
                Serial.println(F("Activating E1"));
            #endif

            powerCtrlActivateElectronics(POWER_ELECTRONIC_CHANNEL1_PIN);
            pPwrManager->pwrManagerOutputStates.stateElectronic1Power = 1;
            pPwrManager->pwrManagerRemoteCommand = REMOTE_CTRL_CMD_UNKNOWN;
            break;

        case REMOTE_CTRL_CMD_POWER_E1_OFF:
            #ifdef PWRMGR_DEBUG
                Serial.println(F("Deactivating E1"));
            #endif

            powerCtrlDeactivateElectronics(POWER_ELECTRONIC_CHANNEL1_PIN);
            pPwrManager->pwrManagerOutputStates.stateElectronic1Power = 0;
            pPwrManager->pwrManagerRemoteCommand = REMOTE_CTRL_CMD_UNKNOWN;
            break;

        case REMOTE_CTRL_CMD_POWER_E2:
            #ifdef PWRMGR_DEBUG
                Serial.println(F("Activating E2"));
            #endif

            powerCtrlActivateElectronics(POWER_ELECTRONIC_CHANNEL2_PIN);
            pPwrManager->pwrManagerOutputStates.stateElectronic2Power = 1;
            pPwrManager->pwrManagerRemoteCommand = REMOTE_CTRL_CMD_UNKNOWN;
            break;

        case REMOTE_CTRL_CMD_POWER_E2_OFF:
            #ifdef PWRMGR_DEBUG
                Serial.println(F("Deactivating E2"));
            #endif

            powerCtrlDeactivateElectronics(POWER_ELECTRONIC_CHANNEL2_PIN);
            pPwrManager->pwrManagerOutputStates.stateElectronic2Power = 0;
            pPwrManager->pwrManagerRemoteCommand = REMOTE_CTRL_CMD_UNKNOWN;
            break;

        case REMOTE_CTRL_CMD_POWER_E3:
            #ifdef PWRMGR_DEBUG
                Serial.println(F("Activating E3"));
            #endif

            powerCtrlActivateElectronics(POWER_ELECTRONIC_CHANNEL3_PIN);
            pPwrManager->pwrManagerOutputStates.stateElectronic3Power = 1;
            pPwrManager->pwrManagerRemoteCommand = REMOTE_CTRL_CMD_UNKNOWN;
            break;

        case REMOTE_CTRL_CMD_POWER_E3_OFF:
            #ifdef PWRMGR_DEBUG
                Serial.println(F("Deactivating E3"));
            #endif

            powerCtrlDeactivateElectronics(POWER_ELECTRONIC_CHANNEL3_PIN);
            pPwrManager->pwrManagerOutputStates.stateElectronic3Power = 0;
            pPwrManager->pwrManagerRemoteCommand = REMOTE_CTRL_CMD_UNKNOWN;
            break;

        case REMOTE_CTRL_CMD_POWER_E4:
            #ifdef PWRMGR_DEBUG
                Serial.println(F("Activating E4"));
            #endif

            powerCtrlActivateElectronics(POWER_ELECTRONIC_CHANNEL4_PIN);
            pPwrManager->pwrManagerOutputStates.stateElectronic4Power = 1;
            pPwrManager->pwrManagerRemoteCommand = REMOTE_CTRL_CMD_UNKNOWN;
            break;

        case REMOTE_CTRL_CMD_POWER_E4_OFF:
            #ifdef PWRMGR_DEBUG
                Serial.println(F("Deactivating E4"));
            #endif

            powerCtrlDeactivateElectronics(POWER_ELECTRONIC_CHANNEL4_PIN);
            pPwrManager->pwrManagerOutputStates.stateElectronic4Power = 0;
            pPwrManager->pwrManagerRemoteCommand = REMOTE_CTRL_CMD_UNKNOWN;
            break;

        case REMOTE_CTRL_CMD_POWER_E_ALL:
            #ifdef PWRMGR_DEBUG
                Serial.println(F("Activating all E Power Stages"));
            #endif

            displayShowPowerControlStartMessage();
            indicatorSpeedBlink(500);

            powerCtrlActivateElectronics(POWER_ELECTRONIC_CHANNEL1_PIN);
            pPwrManager->pwrManagerOutputStates.stateElectronic1Power = 1;
            delay(POWER_STARTUP_STATE_DELAY);

            powerCtrlActivateElectronics(POWER_ELECTRONIC_CHANNEL2_PIN);
            pPwrManager->pwrManagerOutputStates.stateElectronic2Power = 1;
            delay(POWER_STARTUP_STATE_DELAY);

            powerCtrlActivateElectronics(POWER_ELECTRONIC_CHANNEL3_PIN);
            pPwrManager->pwrManagerOutputStates.stateElectronic3Power = 1;
            delay(POWER_STARTUP_STATE_DELAY);

            powerCtrlActivateElectronics(POWER_ELECTRONIC_CHANNEL4_PIN);
            pPwrManager->pwrManagerOutputStates.stateElectronic4Power = 1;
            delay(POWER_STARTUP_STATE_DELAY);

            pPwrManager->pwrManagerRemoteCommand = REMOTE_CTRL_CMD_UNKNOWN;
            break;
    }
}

/**
 *
 * @param pPwrManager
 */
void powerManagerHandlePowerStartMode(PWR_STATE_MACHINE* pPwrManager)
{
	// TODO Check voltage and current

    // Handle the differente remote commands to turn on/off specific stages
	powerManagerHandleStageSwitchCommands(pPwrManager);

	// Check if all Electronic Power Stages have been turned on
	if (pPwrManager->pwrManagerOutputStates.stateElectronic1Power == 1
			&& pPwrManager->pwrManagerOutputStates.stateElectronic2Power == 1
			&& pPwrManager->pwrManagerOutputStates.stateElectronic3Power == 1
			&& pPwrManager->pwrManagerOutputStates.stateElectronic4Power == 1)
	{
		powerManagerSwitchMode(pPwrManager, PWRM_MODE_RUN);

		indicatorLEDBlink(1000);

        #ifdef PWRMGR_DEBUG
            Serial.println(F("[powerManagerRunStateMachine]: Entering Run Mode"));
        #endif
	}
}

/**
 *
 * @param pPwrManager
 */
void powerManagerHandleRunMode(PWR_STATE_MACHINE* pPwrManager)
{
	switch (pPwrManager->pwrManagerRemoteCommand)
    {
        case REMOTE_CTRL_CMD_POWER:
            #ifdef PWRMGR_DEBUG
                Serial.println(F("Switching to Shutdown"));
            #endif

            powerManagerSwitchMode(pPwrManager, PWRM_MODE_SHUTDOWN);
            pPwrManager->pwrManagerRemoteCommand = REMOTE_CTRL_CMD_UNKNOWN;
            break;
    }

	// Handle the differente remote commands to turn on/off specific stages
    powerManagerHandleStageSwitchCommands(pPwrManager);

}

/**
 *
 * @param pPwrManager
 */
void powerManagerHandleShutdown(PWR_STATE_MACHINE* pPwrManager)
{
	#ifdef PWRMGR_DEBUG
		Serial.println(F("Entering Shutdown Mode"));
	#endif

	indicatorSpeedBlink(POWER_SHUTDOWN_DELAY);

	powerCtrlDeactivateElectronics(POWER_ELECTRONIC_CHANNEL4_PIN);
    pPwrManager->pwrManagerOutputStates.stateElectronic4Power = 0;
    indicatorSpeedBlink(POWER_SHUTDOWN_STAGE_DELAY);

	powerCtrlDeactivateElectronics(POWER_ELECTRONIC_CHANNEL3_PIN);
	pPwrManager->pwrManagerOutputStates.stateElectronic3Power = 0;
	indicatorSpeedBlink(POWER_SHUTDOWN_STAGE_DELAY);

	powerCtrlDeactivateElectronics(POWER_ELECTRONIC_CHANNEL2_PIN);
	pPwrManager->pwrManagerOutputStates.stateElectronic2Power = 0;
	indicatorSpeedBlink(POWER_SHUTDOWN_STAGE_DELAY);

	powerCtrlDeactivateElectronics(POWER_ELECTRONIC_CHANNEL1_PIN);
	pPwrManager->pwrManagerOutputStates.stateElectronic1Power = 0;
	indicatorSpeedBlink(POWER_SHUTDOWN_STAGE_DELAY);

	powerManagerSwitchMode(pPwrManager, PWRM_MODE_INIT);
}

/**
 *
 * @param pwrManager
 * @return
 */
int16_t powerManagerRunStateMachine(PWR_STATE_MACHINE* pPwrManager)
{
	switch(pPwrManager->pwrManagerMode)
	{
		case PWRM_MODE_INIT:
		{
			remoteCtrlClearCommands();
			powerManagerSwitchMode(pPwrManager, PWRM_MODE_PRE_POWER);
		}
		break;

		case PWRM_MODE_PRE_POWER:
		{
			powerManagerHandlePrePowerMode(pPwrManager);
		}
		break;

		case PWRM_MODE_POWER_START:
		{
			powerManagerHandlePowerStartMode(pPwrManager);
		}
		break;

		case PWRM_MODE_RUN:
		{
			powerManagerHandleRunMode(pPwrManager);
		}
		break;

		case PWRM_MODE_FAILURE:
		{

		}
		break;

		case PWRM_MODE_SHUTDOWN:
		{
			powerManagerHandleShutdown(pPwrManager);
		}
		break;

		default:
		{
			// If there is a another state, switch directly to failure mode
			powerManagerSwitchMode(pPwrManager, PWRM_MODE_FAILURE);
		}
		break;
	}

	// Update the status LEDs
	powerManagerUpdateUIStatus(pPwrManager);

	return pPwrManager->pwrManagerMode;
}

/**
 *
 */
void powerManagerUpdateUIStatus(PWR_STATE_MACHINE* pPwrManager)
{
    if ( pPwrManager->pwrManagerMode == PWRM_MODE_POWER_START
        || pPwrManager->pwrManagerMode == PWRM_MODE_RUN)
    {
        showMainStatus(STATUS_OK);
    }
    else
    {
        showMainStatus(STATUS_NOK);
    }

    if (pPwrManager->pwrManagerMode == PWRM_MODE_RUN)
    {
        if (pPwrManager->pwrManagerOutputStates.stateElectronic1Power == 1
            && pPwrManager->pwrManagerOutputStates.stateElectronic2Power == 1
            && pPwrManager->pwrManagerOutputStates.stateElectronic3Power == 1
            && pPwrManager->pwrManagerOutputStates.stateElectronic4Power == 1)
        {
            showElectronicStatus(STATUS_OK);
        }
        else
        {
            showElectronicStatus(STATUS_NOK);
        }
    }
    else
    {
        showMotorStatus(STATUS_NOK);
        showElectronicStatus(STATUS_NOK);
    }
}
