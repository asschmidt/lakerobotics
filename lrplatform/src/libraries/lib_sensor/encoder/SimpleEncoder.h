/*
 * SimpleEncoder.h
 *
 *  Created on: 05.10.2018
 *      Author: Andreas
 */

#ifndef SRC_LIBRARIES_ENCODER_SIMPLEENCODER_H_
#define SRC_LIBRARIES_ENCODER_SIMPLEENCODER_H_

#define ENCODER_MAX_TIMESTEP	18000

typedef struct
{
	// Encoder Configuration
	int numberOfCounts;

	// Time calculation values
	unsigned long prevTime;
	unsigned long timestep;

	// Calculated values for speed [rpm] and position
	unsigned long speed;
	long position;

	volatile IO_REG_TYPE * pin1ARegister;
	IO_REG_TYPE            pin1ABitmask;

	volatile IO_REG_TYPE * pin1BRegister;
	IO_REG_TYPE            pin1BBitmask;
} SIMPLE_ENCODER_STATE;

typedef enum
{
	ENCODER1,
	ENCODER2
} SIMPLE_ENCODER_ID;

typedef enum
{
	SPEED_RPM,
	SPEED_RPMS
} SIMPLE_ENCODER_SPEED_TYPE;

class SimpleEncoder
{
	public:
		SimpleEncoder(int numberOfCounts1, int pin1A, int pin1B, int numberOfCounts2, int pin2A, int pin2B);

		long getPosition(SIMPLE_ENCODER_ID encoderID);
		unsigned long getSpeed(SIMPLE_ENCODER_ID encoderID, SIMPLE_ENCODER_SPEED_TYPE speedType);

	private:
		static SIMPLE_ENCODER_STATE encoderState1;
		static SIMPLE_ENCODER_STATE encoderState2;

	protected:
		static SIMPLE_ENCODER_STATE* actualEncoder1;
		static SIMPLE_ENCODER_STATE* actualEncoder2;

		static void handleEncoder1A();
		static void handleEncoder2A();

		static void handleEncoder(SIMPLE_ENCODER_STATE* pEncoder);
};

#endif /* SRC_LIBRARIES_ENCODER_SIMPLEENCODER_H_ */
