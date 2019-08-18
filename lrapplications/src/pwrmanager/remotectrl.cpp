/*
 * remotectrl.cpp
 *
 *  Created on: 27.07.2018
 *      Author: Andreas
 */

#include "common.h"
#include "hwconfig.h"
#include "remotectrl.h"
#include "gen/Node_Pwr_CAN.h"

#include "cbuffer/CircularBuffer.h"
#include "queue/QueueArray.h"

#include "cmdparser/CmdBuffer.hpp"
#include "cmdparser/CmdCallback.hpp"
#include "cmdparser/CmdParser.hpp"

#include "debounce/ButtonDebounce.h"

static CircularBuffer<int16_t, 5> g_remoteCmdBuffer;

static CmdCallback_P<3> cmdCallback;
static CmdBuffer<32> cmdBuffer;
static CmdParser cmdParser;

static ButtonDebounce mainButton;
static ButtonDebounce activateButton1;
static ButtonDebounce activateButton2;

static RemoteCtrl_CAN_PowerControl g_PowerCtrlMsg;

static void remoteCtrlProcessActivate(CmdParser* cmdParser);

/**
 *
 */
void remoteCtrlInitialize()
{
    g_PowerCtrlMsg.messageValid = false;
    g_PowerCtrlMsg.CAN_PowerControlMsg.Power_Electronic_1_Active = 0;
    g_PowerCtrlMsg.CAN_PowerControlMsg.Power_Electronic_2_Active = 0;
    g_PowerCtrlMsg.CAN_PowerControlMsg.Power_Electronic_3_Active = 0;
    g_PowerCtrlMsg.CAN_PowerControlMsg.Power_Electronic_4_Active = 0;

	cmdCallback.addCmd(PSTR("ACT"), &remoteCtrlProcessActivate);

	mainButton.initializeButton(BUTTON_MAIN_PIN, 100);
	activateButton1.initializeButton(BUTTON_START1_PIN, 100);
	activateButton2.initializeButton(BUTTON_START2_PIN, 100);
}

/**
 *
 */
void remoteCtrlClearCommands()
{
	g_remoteCmdBuffer.clear();
}

/**
 *
 * @return
 */
int16_t remoteCtrlProcessCommands()
{
	// read data
	if (cmdBuffer.readFromSerial(&Serial, 1))
	{
		// parse command line
		if (cmdParser.parseCmd(&cmdBuffer) != CMDPARSER_ERROR)
		{
			// search command in store and call function
			if (cmdCallback.processCmd(&cmdParser))
			{
				// FIXME: handling cmd not found
			}
			cmdBuffer.clear();
		}
	}
	else if (g_PowerCtrlMsg.messageValid == true)
	{
	    Serial.println("Got valid Power Control CAN Message");

	    if (g_PowerCtrlMsg.CAN_PowerControlMsg.Power_Electronic_1_Active == 1)
	    {
	        g_remoteCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E1);
	    }
	    else
	    {
	        g_remoteCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E1_OFF);
	    }

	    if (g_PowerCtrlMsg.CAN_PowerControlMsg.Power_Electronic_2_Active == 1)
        {
            g_remoteCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E2);
        }
	    else
	    {
	        g_remoteCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E2_OFF);
	    }

	    if (g_PowerCtrlMsg.CAN_PowerControlMsg.Power_Electronic_3_Active == 1)
        {
            g_remoteCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E3);
        }

	    if (g_PowerCtrlMsg.CAN_PowerControlMsg.Power_Electronic_4_Active == 1)
        {
            g_remoteCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E4);
        }

	    // Finally set the message object to invalid
	    g_PowerCtrlMsg.messageValid = false;
	}
	else
	{
	    mainButton.update();
	    activateButton1.update();
	    activateButton2.update();

	    // If the main button is pressed, activate the state machine
		if (mainButton.state() == LOW)
		{
		    g_remoteCmdBuffer.push(REMOTE_CTRL_CMD_POWER);
		}
		else if (activateButton1.state() == LOW)
        {
            g_remoteCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E_ALL);
        }
	}

	return g_remoteCmdBuffer.available();
}

/**
 *
 * @return
 */
int16_t remoteCtrlGetNextCommand()
{
	if (!g_remoteCmdBuffer.isEmpty())
	{
		return g_remoteCmdBuffer.pop();
	}
	else
	{
		return REMOTE_CTRL_CMD_UNKNOWN;
	}
}

/**
 *
 * @return
 */
RemoteCtrl_CAN_PowerControl* remoteCtrlGetMsgPowerControl()
{
    return &g_PowerCtrlMsg;
}

/**
 *
 * @param cmdParser
 */
void remoteCtrlProcessActivate(CmdParser* cmdParser)
{
	Serial.println("Got Activate Command");

	if (cmdParser->equalCmdParam_P(1, PSTR("E1")))
	{
		Serial.println("Activating E1");
		g_remoteCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E1);
	}
	else if (cmdParser->equalCmdParam_P(1, PSTR("E2")))
	{
		Serial.println("Activating E2");
		g_remoteCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E2);
	}
	else if (cmdParser->equalCmdParam_P(1, PSTR("E3")))
	{
		Serial.println("Activating E3");
		g_remoteCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E3);
	}
	else if (cmdParser->equalCmdParam_P(1, PSTR("E4")))
    {
        Serial.println("Activating E4");
        g_remoteCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E4);
    }
	else if (cmdParser->equalCmdParam_P(1, PSTR("EALL")))
	{
		Serial.println("Activating EAll");
		g_remoteCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E_ALL);
	}
}
