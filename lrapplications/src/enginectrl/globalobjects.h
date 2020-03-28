/*
 * globalobjects.h
 *
 *  Created on: 23.03.2020
 *      Author: avsch
 */

#ifndef LRAPPLICATIONS_SRC_ENGINECTRL_GLOBALOBJECTS_H_
#define LRAPPLICATIONS_SRC_ENGINECTRL_GLOBALOBJECTS_H_

#include "parametermodel.h"
#include "processmodel.h"
#include "encoder.h"
#include "canhandler.h"

extern EngineCtrlParameterModel gParameterModel;
extern EngineCtrlProcessModel gProcessModel;
extern EncoderModel gEncoderModel;

extern CANTransmissionTableEntry gCANTransmissionTable[];
extern int16_t gCANTableEntryCount;

extern CANHandler gCANHandler;

#endif /* LRAPPLICATIONS_SRC_ENGINECTRL_GLOBALOBJECTS_H_ */
