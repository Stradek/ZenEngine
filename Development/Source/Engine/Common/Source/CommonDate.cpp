/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "CommonDate.h"

namespace Engine::Common
{
	Date::Date(std::time_t timeNow)
	{
		localtime_s(&m_timeInfo, &timeNow);
	}

	size_t Date::GetYear() const
	{
		return m_timeInfo.tm_year + 1900;
	}

	size_t Date::GetMonth() const
	{
		return m_timeInfo.tm_mon + 1;
	}

	size_t Date::GetDay() const
	{
		return m_timeInfo.tm_mday;
	}

	Date GetCurrentDate()
	{
		auto now = std::chrono::system_clock::now();
		std::time_t timeNow = std::chrono::system_clock::to_time_t(now);

		Date date(timeNow);
		return date;
	}
}
