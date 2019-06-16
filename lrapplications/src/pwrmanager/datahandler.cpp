/*
 * datahandler.cpp
 *
 *  Created on: 18.12.2018
 *      Author: Andreas
 */
#include "common.h"
#include "hwconfig.h"

#include "datahandler.h"

static DataCollector<MAX_DATA_ITEMS> g_DataCollector;

/**
 *
 * @return
 */
DataCollector<MAX_DATA_ITEMS>* dataGetCollector()
{
	return &g_DataCollector;
}
