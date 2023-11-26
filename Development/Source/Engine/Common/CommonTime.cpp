/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "CommonTime.h"


namespace Engine::Common
{
	Time Time::GetTimeNow()
	{
		uint64 timeSinceEpoch = static_cast<uint64>(high_res_clock::now().time_since_epoch().count());
		Time timeNow = Time(timeSinceEpoch);
		return timeNow;
	}

	double Time::GetHours() const
	{
		return GetNanoseconds() * NANOSECOND_TO_HOUR;
	}

	double Time::GetMinutes() const
	{
		return GetNanoseconds() * NANOSECOND_TO_MINUTE;
	}

	double Time::GetSeconds() const
	{
		return GetNanoseconds() * NANOSECOND_TO_SECOND;
	}

	double Time::GetMilliseconds() const
	{
		return GetNanoseconds() * NANOSECOND_TO_MILLISECOND;
	}

	uint64 Time::GetNanoseconds() const
	{
		return m_nanosecondTime;
	}
}