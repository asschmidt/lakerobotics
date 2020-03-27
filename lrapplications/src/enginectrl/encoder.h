/*
 * encoder.h
 *
 *  Created on: 23.03.2020
 *      Author: avsch
 */

#ifndef LRAPPLICATIONS_SRC_ENGINECTRL_ENCODER_H_
#define LRAPPLICATIONS_SRC_ENGINECTRL_ENCODER_H_

#include <stdint.h>

#define ENC_QUADRANT_I          1
#define ENC_QUADRANT_II         2
#define ENC_QUADRANT_III        3
#define ENC_QUADRANT_VI         4

typedef struct _Encoder_Model
{
        uint16_t currentValueM1;
        uint16_t currentValueM2;

        uint16_t lastValueM1;
        uint16_t lastValueM2;

        uint16_t quadrantMotorSide;          //!< Number of counts for one quadrant at the motor side
        uint16_t quadrantGearboxSide;        //!< Number of counts for one quadrant at the gearbox side
} EncoderModel;

extern int32_t encoderInitialize(EncoderModel* pEncoderModel);
extern EncoderModel* encoderGetModel();

extern int32_t encoderGetCounterValues(EncoderModel* pEncoderModel, uint16_t* pEncM1, uint16_t* pEncM2);
extern int32_t encoderCalculateDiff(EncoderModel* pEncoderModel, int16_t* diffEncM1, int16_t* diffEncM2);

extern int8_t encoderGetQuadrant(EncoderModel* pEncoderModel, uint16_t encValue);
extern bool encoderCheckForQuadrant(EncoderModel* pEncoderModel, int8_t quadrantNo, uint16_t encoderCount);

#endif /* LRAPPLICATIONS_SRC_ENGINECTRL_ENCODER_H_ */
