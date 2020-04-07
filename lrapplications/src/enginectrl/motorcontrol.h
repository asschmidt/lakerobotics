/*
 * motorcontrol.h
 *
 *  Created on: 29.03.2020
 *      Author: avsch
 */

#ifndef LRAPPLICATIONS_SRC_ENGINECTRL_MOTORCONTROL_H_
#define LRAPPLICATIONS_SRC_ENGINECTRL_MOTORCONTROL_H_

#include <stdint.h>

//#define PID_FIND_PARAMETER          1

#define DEFAULT_MIN_OUTPUT          -1000
#define DEFAULT_MAX_OUTPUT          1000
#define DEFAULT_CONTROL_FREQUENCY   100

typedef struct _MotorControl
{
        float       kpLeftEngine;
        float       kiLeftEngine;
        float       kdLeftEngine;

        float       kpRightEngine;
        float       kiRightEngine;
        float       kdRightEngine;

        int16_t     minOutput;
        int16_t     maxOutput;

        int16_t     pidFrequency;
} MotorControl;

extern int32_t motorControlInitialize(MotorControl* pControl);
extern int32_t motorControlRun(MotorControl* pControl);

extern int32_t motorControlFindParameter(MotorControl* pControl);
extern int32_t motorControlGetStepResponse(MotorControl* pControl);

#endif /* LRAPPLICATIONS_SRC_ENGINECTRL_MOTORCONTROL_H_ */
