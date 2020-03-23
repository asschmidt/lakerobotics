/*
 * processmodel.h
 *
 *  Created on: 22.03.2020
 *      Author: avsch
 */

#ifndef LRAPPLICATIONS_SRC_ENGINECTRL_PROCESSMODEL_H_
#define LRAPPLICATIONS_SRC_ENGINECTRL_PROCESSMODEL_H_

#include <stdint.h>

/*
 * Definition of the direction
 */
#define WHEEL_DIRECTION_FORWARD     0
#define WHEEL_DIRECTION_BACKWARD    1

/*
 * Structure which defines the process model of the Engine Ctrl
 * This includes the CAN values and also values from peripherals like ADC and GPIO
 */
typedef struct _EngineCtrl_ProcessModel
{
        int16_t _rawDeltaCountLeft;         //!< Raw value of encoder delta for left engine
        int16_t _rawDeltaCountRight;        //!< Raw value of encoder delta for right engine

        int16_t _rawDeltaLastCountLeft;     //!< Last value of raw encoder delta for left engine
        int16_t _rawDeltaLastCountRight;    //!< Last value of raw encoder delta for right engine

        int16_t wheelSpeedLeft;             //!< Wheel speed left
        int16_t wheelSpeedRight;            //!< Wheel speed right

        int16_t wheelSetpointSpeedLeft;     //!< Engine speed setpoint in rpm for left wheel
        int16_t wheelSetpointSpeedRight;    //!< Engine speed setpoint in rpm for right wheel

        int16_t engineSpeedLeft;            //!< Engine speed in rpm for the left wheel
        int16_t engineSpeedLastLeft;        //!< Engine speed stored during the last sample run

        int16_t engineSpeedRight;           //!< Engine speed in rpm for the right wheel
        int16_t engineSpeedLastRight;       //!< Engine speed stored during the last sample run

        int16_t engineAngleSpeedLeft;       //!< Engine angle speed left [Base: rad/s, Scale: 1000]
        int16_t engineAngleSpeedRight;      //!< Engine angle speed right [Base: rad/s, Scale: 1000]

        int16_t engineAccelerationLeft;     //!< Current acceleration of left engine [Base: rad/s^2, Scale: 1000]
        int16_t engineAccelerationRight;    //!< Current acceleration of right engine [Base: rad/s^2, Scale: 1000]

        uint16_t pwmLeft;                   //!< PWM value for H-Bridge of left engine
        uint16_t pwmRight;                  //!< PWM value for H-Bridge of right engine
} EngineCtrlProcessModel;

extern int32_t processModelInitialize(EngineCtrlProcessModel* pModel);
extern EngineCtrlProcessModel* processModelGetModel();

extern int32_t processModelSetEngineSpeed(EngineCtrlProcessModel* pModel, int16_t rawDeltaCountLeft, int16_t rawDeltaCountRight);

#endif /* LRAPPLICATIONS_SRC_ENGINECTRL_PROCESSMODEL_H_ */
