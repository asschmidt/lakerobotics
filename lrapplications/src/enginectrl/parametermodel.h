/*
 * parametermodel.h
 *
 *  Created on: 23.03.2020
 *      Author: avsch
 */

#ifndef LRAPPLICATIONS_SRC_ENGINECTRL_PARAMETERMODEL_H_
#define LRAPPLICATIONS_SRC_ENGINECTRL_PARAMETERMODEL_H_

#include <stdint.h>

/*
 * Some parameter default values based on J2P configuration
 */
#define PI_FLOAT                3.141592
#define PI_SCALE_1000           3141

#define DEFAULT_KX_VALUE        1.0             //!< Default value for K parameter of an PID controller
#define DEFAULT_SAMPLE_TIME     10              //!< Sample time of 10ms

#define WHEEL_DIAMETER          120             //!< 120mm Wheel diameter
#define GEARBOX_RATIO           131.25          //!< Gear box ratio of 1:131
#define ENCODER_COUNTS          64              //!< Encoder counts per revolution of the motor

/*!
 * Definition of a structure which holds all parameter for the Engine control
 * This structure could be saved in NVM
 */
typedef struct _EngineCtrl_ParameterModel
{
        float kpLeftEngine;             //!< KP Parameter for PID of Left Engine
        float kiLeftEngine;             //!< KI Parameter for PID of Left Engine
        float kdLeftEngine;             //!< KD Parameter for PID of Left Engine

        float kpRightEngine;            //!< KP Parameter for PID of Right Engine
        float kiRightEngine;            //!< KI Parameter for PID of Right Engine
        float kdRightEngine;            //!< KD Parameter for PID of Right Engine

        int16_t wheelDiameter;          //!< Diameter of the wheel in mm
        int16_t encoderCounts;          //!< Number of counts of the wheel encoder per revolution of motor
        float gearboxRatio;             //!< Gearbox ratio in 1:x

        int16_t sampleTime;             //!< Sample time of the PID controller

} EngineCtrlParameterModel;

extern int32_t paramModelInitialize(EngineCtrlParameterModel* pParamModel);
extern int32_t paramModelInitializeDefaults(EngineCtrlParameterModel* pParamModel);

extern EngineCtrlParameterModel* paramModelGetModel();

#endif /* LRAPPLICATIONS_SRC_ENGINECTRL_PARAMETERMODEL_H_ */
