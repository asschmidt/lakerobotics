/*
 * DataCollector.h
 *
 *  Created on: 18.12.2018
 *      Author: Andreas
 */

#ifndef SRC_LIBRARIES_DATACOLLECT_DATACOLLECTOR_H_
#define SRC_LIBRARIES_DATACOLLECT_DATACOLLECTOR_H_

#include <inttypes.h>

#include <Print.h>

/**
 *
 */
template<uint16_t S> class DataCollector
{
public:
		DataCollector();

		int16_t updateData(uint16_t idx, int16_t data);
		uint32_t update32BitData(uint16_t idx, uint32_t data);

		int16_t printData(Print& printer);

private:
		int16_t dataArray[S];		//!< Holds the data array
};

#include "DataCollector.tpp"

#endif /* SRC_LIBRARIES_DATACOLLECT_DATACOLLECTOR_H_ */
