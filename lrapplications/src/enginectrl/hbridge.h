/*
 * hbridge.h
 *
 *  Created on: 22.03.2020
 *      Author: avsch
 */

#ifndef LRAPPLICATIONS_SRC_ENGINECTRL_HBRIDGE_H_
#define LRAPPLICATIONS_SRC_ENGINECTRL_HBRIDGE_H_

#include <stdint.h>

/*
 * Definition of different H-Bridge types which the module can handle
 */
#define H_BRIDGE_TYPE_L298          1
#define H_BRIDGE_TYPE_VNH25         2

/*
 * Definition of the H-Bridge channel (Left wheel, right wheel)
 */
#define H_BRIDGE_LEFT               0
#define H_BRIDGE_RIGHT              1

/*
 * Definition of the different direction modes the H-Bridge can handle
 */
#define H_BRIDGE_STOP               0
#define H_BRIDGE_FORWARD            1
#define H_BRIDGE_BACKWARD           2

/*
 * Public API for the H-Bridge
 */
extern void bridgeInitialize(void);
extern int32_t bridgeSetDirection(int8_t bridgeChannel, int8_t direction);
extern int32_t bridgeSetPWMValue(int8_t bridgeChannel, uint16_t pwmValue);

#endif /* LRAPPLICATIONS_SRC_ENGINECTRL_HBRIDGE_H_ */
