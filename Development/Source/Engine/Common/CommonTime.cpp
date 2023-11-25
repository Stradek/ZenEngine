/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "CommonTime.h"

using std::chrono::duration_cast;

/*
	IMPORTANT NOTICE:
	This class doesn't support downcasting.
	std::chrono::seconds downcasted to std::chrono::nanoseconds will cause data lose etc.
	Only classes in Engine::Common::Time should use other time and duration types.

	For engine computations use uint32.
	For engine string data use double.

	NOTE:
	Seconds are used as a default value for double.
	Nanoseconds are used as a default value for engine computations.
	UInt32 is raw representation of Nanoseconds.
*/

namespace Engine::Common
{
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

	size_t Time::GetNanoseconds() const
	{
		return m_nanosecondsTime.count();
	}

	Time GetTimeNow()
	{
		size_t timeSinceEpoch = high_res_clock::now().time_since_epoch().count();

		Time timeNow = Time(timeSinceEpoch);
		return timeNow;
	}
}