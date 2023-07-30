/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "CommonDate.h"

namespace Engine::Common::DateTime
{
	Date GetCurrentDate()
	{
		auto now = std::chrono::system_clock::now();
		std::time_t timeNow = std::chrono::system_clock::to_time_t(now);

		std::unique_ptr<std::tm> timeStruct = std::make_unique<std::tm>(*std::localtime(&timeNow));

		Date date;
		date.year = timeStruct->tm_year + 1900; // Years since 1900
		date.month = timeStruct->tm_mon + 1; // Months are represented as 0-11
		date.day = timeStruct->tm_mday;

		return date;
	}
}
