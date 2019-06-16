/*
 * L298.h
 *
 *  Created on: 05.10.2018
 *      Author: Andreas
 */

#ifndef SRC_LIBRARIES_L298_L298_H_
#define SRC_LIBRARIES_L298_L298_H_

/**
 *
 */
typedef enum
{
	STOP,
	FORWARD,		//!< FORWARD
	REVERSE 		//!< REVERSE
} L298_DIRECTION;

/**
 *
 */
typedef enum
{
	NORMAL,      	//!< NORMAL
	BIDIRECTIONAL	//!< BIDIRECTIONAL
} L298_MODE;

/**
 *
 */
class L298
{
	public:
		L298(int enaPin, int in1Pin, int in2Pin);

		void setMode(L298_MODE m);
		L298_MODE getMode();

		void setDirection(L298_DIRECTION direction);
		L298_DIRECTION getDirection();

		void setSpeed(int speed);
		void stop();

	private:
		void setInternalDirection(L298_DIRECTION dir);

	private:
		L298_DIRECTION direction;
		L298_MODE mode;

		int enablePin;
		int input1Pin;
		int input2Pin;
};


#endif /* SRC_LIBRARIES_L298_L298_H_ */
