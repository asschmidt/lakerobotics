/*
 * main.cpp
 *
 *  Created on: 17.12.2018
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

#ifdef USE_DATA_HANDLER
	#include "datahandler.h"
#endif

#include "tasksched/TaskScheduler.h"
#include "debughelp/DebugHelp.h"

static void taskCANHandler();
static void taskPowerManager();
static void taskDisplay();
static void taskMeasurement();
static void taskRemoteController();

#ifdef USE_DATA_HANDLER
	static void taskDataHandler();
#endif

static Scheduler g_Scheduler;
static PWR_STATE_MACHINE g_pwrManager;

/**
 * Task definitions for the Power Manager Application
 */
Task tskCAN(POWER_MANAGER_CAN_CYCLE, TASK_FOREVER, &taskCANHandler);
Task tskRemote(POWER_MANAGER_CAN_CYCLE, TASK_FOREVER, &taskRemoteController);
Task tskMeasurement(POWER_MANAGER_MEASUREMENT_CYCLE, TASK_FOREVER, &taskMeasurement);
Task tskPowerManager(POWER_MANAGER_LOOP_CYCLE, TASK_FOREVER, &taskPowerManager);
Task tskDisplay(POWER_MANAGER_DISPLAY_CYCLE, TASK_FOREVER, &taskDisplay);

#ifdef USE_DATA_HANDLER
	Task tskDataHandler(POWER_MANAGER_CAN_CYCLE, TASK_FOREVER, &taskDataHandler);
#endif

/**
 *
 */
void setup()
{
	// Initialize with INIT state
	powerManagerInitialize(&g_pwrManager);

	Serial.begin(115200);
	Serial.println(F("J2P Bot - PowerManager initializing...."));

	g_Scheduler.init();

	Serial.println(F("Initializing Display"));
	displayInitialize();
	displayShowStartupMessage();

	Serial.println(F("Initializing ADC"));
	measurementInitialize();

	Serial.println(F("Initializing CAN"));
	canHandlerInitialize(CAN_500KBPS);

	Serial.println(F("Initializing GPIO for Relays"));
	powerCtrlInitialize();

	Serial.println(F("Initializing IR Remote Control"));
	remoteCtrlInitialize();

	Serial.println(F("Initializing Indicator"));
	indicatorInitialize();

	indicatorBuzz(200);

	// Switch to pre-power mode
	powerManagerSwitchMode(&g_pwrManager, PWRM_MODE_PRE_POWER);

	g_Scheduler.addTask(tskMeasurement);
	tskMeasurement.enable();

	g_Scheduler.addTask(tskPowerManager);
	tskPowerManager.enable();

	g_Scheduler.addTask(tskRemote);
	tskRemote.enable();

	g_Scheduler.addTask(tskCAN);
	tskCAN.enable();

	g_Scheduler.addTask(tskDisplay);
	tskDisplay.enable();

#ifdef USE_DATA_HANDLER
	g_Scheduler.addTask(tskDataHandler);
	tskDataHandler.enable();
#endif
}

/**
 *
 */
void loop()
{
	// Run the main Scheduler
	g_Scheduler.execute();
}

/**
 *
 */
void taskCANHandler()
{
#ifdef USE_DATA_HANDLER
	uint32_t startTime = startRuntimeMeasurement();
#endif

	MEASUREMENT_VALUES* pValues = measurementGetValues();
	int16_t currentElectronics = (int16_t)(pValues->currentElectronics * 1000);
	int16_t voltageElectronics = (int16_t)(pValues->voltageElectronics * 1000);
	int16_t currentMotor = (int16_t)(pValues->currentMotor * 1000);
	int16_t voltageMotor = (int16_t)(pValues->voltageMotor * 1000);

	int16_t sendError = 0;
	sendError = canHandlerTransmitElectronicValues(currentElectronics, voltageElectronics);
	if (sendError != 0)
	{
		#ifdef PWRMGR_DEBUG
			Serial.println(F("Error while Sending PWRMANAGER_TX_ELECTRONIC_VALUES_ID"));
		#endif
	}

	sendError = canHandlerTransmitMotorValues(currentMotor, voltageMotor);
	if (sendError != 0)
	{
		#ifdef PWRMGR_DEBUG
			Serial.println(F("Error while Sending PWRMANAGER_TX_MOTOR_VALUES_ID"));
		#endif
	}

	// Handle CAN Receive
	RemoteCtrl_CAN_PowerControl* pCANRemoteControl = remoteCtrlGetMsgPowerControl();
	canHandlerProcessReceiveMessages(pCANRemoteControl);

#ifdef USE_DATA_HANDLER
	uint32_t stopTime = stopRuntimeMeasurement();
	dataGetCollector()->updateData(DATA_ITEM_CAN_TASK, getRuntime(startTime, stopTime));
#endif
}

/**
 *
 */
void taskPowerManager()
{
#ifdef USE_DATA_HANDLER
	uint32_t startTime = startRuntimeMeasurement();
#endif

	// Run the PowerManager state machine
	powerManagerRunStateMachine(&g_pwrManager);

#ifdef USE_DATA_HANDLER
	uint32_t stopTime = stopRuntimeMeasurement();
	dataGetCollector()->updateData(DATA_ITEM_PWRMGR_TASK, getRuntime(startTime, stopTime));
#endif
}

/**
 *
 */
void taskDisplay()
{
	MEASUREMENT_VALUES* pValues = measurementGetValues();
	displayShowMeasurementValues(pValues->voltageMotor, pValues->voltageElectronics, pValues->currentMotor, pValues->currentElectronics);
}

/**
 *
 */
void taskMeasurement()
{
#ifdef USE_DATA_HANDLER
	uint32_t startTime = startRuntimeMeasurement();
#endif

	measurementPerformMeasurement();

#ifdef USE_DATA_HANDLER
	MEASUREMENT_VALUES* pValues = measurementGetValues();
	dataGetCollector()->updateData(DATA_ITEM_VOLTAGE_ELEC, (int16_t)(pValues->voltageElectronics * 1000));
	dataGetCollector()->updateData(DATA_ITEM_VOLTAGE_MOTOR, (int16_t)(pValues->voltageMotor * 1000));
	dataGetCollector()->updateData(DATA_ITEM_CURRENT_ELEC, (int16_t)(pValues->currentElectronics * 1000));
	dataGetCollector()->updateData(DATA_ITEM_CURRENT_MOTOR, (int16_t)(pValues->currentMotor * 1000));
#endif

#ifdef USE_DATA_HANDLER
	uint32_t stopTime = stopRuntimeMeasurement();
	dataGetCollector()->updateData(DATA_ITEM_MEASUREMENT_TASK, getRuntime(startTime, stopTime));
#endif
}

/**
 *
 */
void taskRemoteController()
{
	// Process the remote commands
	remoteCtrlProcessCommands();
	int16_t currentCommand = remoteCtrlGetNextCommand();

	if (currentCommand != REMOTE_CTRL_CMD_UNKNOWN)
	{
		g_pwrManager.pwrManagerRemoteCommand = currentCommand;
	}
}

#ifdef USE_DATA_HANDLER
/**
 *
 */
void taskDataHandler()
{
	DataCollector<MAX_DATA_ITEMS>* pData = dataGetCollector();
	pData->printData(Serial);
}
#endif
