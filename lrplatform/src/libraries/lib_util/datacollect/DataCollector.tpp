/*
 * DataCollector.tpp
 *
 *  Created on: 18.12.2018
 *      Author: Andreas
 */

/**
 *
 * @param printer
 */
template<uint16_t S>
DataCollector<S>::DataCollector()
{

}

/**
 *
 * @param idx
 * @param data
 * @return
 */
template<uint16_t S>
int16_t DataCollector<S>::updateData(uint16_t idx, int16_t data)
{
	int16_t oldData = 0;

	if (idx < S)
	{
		oldData = this->dataArray[idx];
		this->dataArray[idx] = data;
	}

	return oldData;
}

/**
 *
 * @param idx
 * @param data
 * @return
 */
template<uint16_t S>
uint32_t DataCollector<S>::update32BitData(uint16_t idx, uint32_t data)
{
	uint32_t oldData = 0;

	if (idx < S && ((idx + 1) < S))
	{
		oldData = this->dataArray[idx];
		this->dataArray[idx] = (int16_t)((data & 0xFFFF) >> 16);
		this->dataArray[idx + 1] = (int16_t)(data & 0x0000FFFF);
	}

	return oldData;
}

/**
 *
 * @param printer
 * @return
 */
template<uint16_t S>
int16_t DataCollector<S>::printData(Print& printer)
{
	printer.print(F("@"));

	for (uint16_t idx = 0; idx < S - 1; idx++)
	{
		printer.print(this->dataArray[idx]);
		printer.print(F(";"));
	}

	printer.print(this->dataArray[S - 1]);
	printer.println();

	return S;
}
