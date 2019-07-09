/*
 * Utils.cpp
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */

// Std includes
#include <string>
#include <vector>

// Project includes
#include "Utils.h"

/**
 * Splits the provided string based on the separator and returns a vector of strings
 */
std::vector<std::string> split(const std::string& s, char seperator)
{
	std::vector<std::string> output;

	std::string::size_type prev_pos = 0, pos = 0;

	while ((pos = s.find(seperator, pos)) != std::string::npos)
	{
		std::string substring(s.substr(prev_pos, pos - prev_pos));

		output.push_back(substring);

		prev_pos = ++pos;
	}

	output.push_back(s.substr(prev_pos, pos - prev_pos)); // Last word

	return output;
}
