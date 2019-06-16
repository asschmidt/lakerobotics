/*
 * remotectrl.cpp
 *
 *  Created on: 27.07.2018
 *      Author: Andreas
 */

#include "common.h"
#include "hwconfig.h"
#include "remotectrl.h"

#include "iremote/IRremote.h"
#include "cbuffer/CircularBuffer.h"

#include "cmdparser/CmdBuffer.hpp"
#include "cmdparser/CmdCallback.hpp"
#include "cmdparser/CmdParser.hpp"

static IRrecv g_irReceiver(IR_RECEIVER_PIN, IR_RECEIVER_BLINK_PIN);
static decode_results g_irResults;
static CircularBuffer<int, 4> g_irCmdBuffer;

static CmdCallback_P<3> cmdCallback;
static CmdBuffer<32> cmdBuffer;
static CmdParser cmdParser;

static int remoteCtrlDecodeCommands(decode_results* pResults);
static void remoteCtrlProcessActivate(CmdParser* cmdParser);

/**
 *
 */
void remoteCtrlInitialize()
{
	cmdCallback.addCmd(PSTR("ACT"), &remoteCtrlProcessActivate);
	g_irReceiver.enableIRIn();
}

/**
 *
 */
void remoteCtrlClearCommands()
{
	g_irCmdBuffer.clear();
}

/**
 *
 * @return
 */
int remoteCtrlProcessCommands()
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

		return g_irCmdBuffer.available();
	}
	else
	{
		int decodeResultAvailable = g_irReceiver.decode(&g_irResults);

		if (decodeResultAvailable)
		{
			int remoteCmd = remoteCtrlDecodeCommands(&g_irResults);
			g_irCmdBuffer.push(remoteCmd);

			g_irReceiver.resume();
		}

		return g_irCmdBuffer.available();
	}
}

/**
 *
 * @return
 */
int remoteCtrlGetNextCommand()
{
	if (!g_irCmdBuffer.isEmpty())
	{
		return g_irCmdBuffer.pop();
	}
	else
	{
		return REMOTE_CTRL_CMD_UNKNOWN;
	}
}

/**
 *
 * @param pResults
 * @return
 */
int remoteCtrlDecodeCommands(decode_results* pResults)
{
	switch (pResults->value)
	{
		case REMOTE_CTRL_POWER:
			return REMOTE_CTRL_CMD_POWER;

		case REMOTE_CTRL_NUM_1:
			return REMOTE_CTRL_CMD_POWER_E1;

		case REMOTE_CTRL_NUM_2:
			return REMOTE_CTRL_CMD_POWER_E2;

		case REMOTE_CTRL_NUM_3:
			return REMOTE_CTRL_CMD_POWER_E3;

		case REMOTE_CTRL_EQ:
			return REMOTE_CTRL_CMD_POWER_E_ALL;

		default:
			return REMOTE_CTRL_CMD_UNKNOWN;
	}
}

/**
 *
 * @param cmdParser
 */
void remoteCtrlProcessActivate(CmdParser* cmdParser)
{
	Serial.println("Got Activate Command");

	if (cmdParser->equalCmdParam_P(1, PSTR("MAIN")))
	{
		Serial.println("Activating Main");
		g_irCmdBuffer.push(REMOTE_CTRL_CMD_POWER);
	}
	else if (cmdParser->equalCmdParam_P(1, PSTR("E1")))
	{
		Serial.println("Activating E1");
		g_irCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E1);
	}
	else if (cmdParser->equalCmdParam_P(1, PSTR("E2")))
	{
		Serial.println("Activating E2");
		g_irCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E2);
	}
	else if (cmdParser->equalCmdParam_P(1, PSTR("E3")))
	{
		Serial.println("Activating E3");
		g_irCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E3);
	}
	else if (cmdParser->equalCmdParam_P(1, PSTR("EALL")))
	{
		Serial.println("Activating EAll");
		g_irCmdBuffer.push(REMOTE_CTRL_CMD_POWER_E_ALL);
	}
	else if (cmdParser->equalCmdParam_P(1, PSTR("MOTOR")))
	{
		Serial.println("Activating Motor");
		g_irCmdBuffer.push(REMOTE_CTRL_CMD_POWER_MOTOR);
	}
}
