/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "CommonDate.h"

namespace Engine::Common
{
	Date Date::GetCurrentDate()
	{
		auto now = std::chrono::system_clock::now();
		std::time_t timeNow = std::chrono::system_clock::to_time_t(now);

		Date date(timeNow);
		return date;
	}

	Date::Date(tm dateTimeInfo)
	{
		m_dateTimeInfo = dateTimeInfo;
	}

	size_t Date::GetYear() const
	{
		return m_dateTimeInfo.tm_year + 1900;
	}

	size_t Date::GetMonth() const
	{
		return m_dateTimeInfo.tm_mon + 1;
	}

	size_t Date::GetDay() const
	{
		return m_dateTimeInfo.tm_mday;
	}
}
