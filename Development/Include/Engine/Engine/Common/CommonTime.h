/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "TimeTypes.h"
#include "Defines.h"

/*
	NOTE:
	Seconds are used as a default value for double.
	Nanoseconds are used as a default value for engine computations.
	UInt32 is raw representation of Nanoseconds.
*/

namespace Engine::Common::DateTime
{
	struct TimeDetails
	{
		uint hours;
		uint minutes;
		uint seconds;
		uint miliseconds;
		uint nanoseconds;
	};

	class Time
	{
	public:
		Time(uint32 rawTime) : m_rawTime(rawTime) {}

		TimeDetails GetTime() const;
		uint32 GetTimeRaw() const;

	private:
		uint32 m_rawTime;
	};

	static constexpr uint32 HOUR_TO_NANOSECONDS = static_cast<uint32>(
		nanoseconds(hours(1)).count()
	);

	static constexpr uint32 MINUTE_TO_NANOSECONDS = static_cast<uint32>(
		nanoseconds(minutes(1)).count()
	);

	static constexpr uint32 SECOND_TO_NANOSECONDS = static_cast<uint32>(
		nanoseconds(seconds(1)).count()
	);
	static constexpr uint32 MILISECOND_TO_NANOSECONDS = static_cast<uint32>(
		nanoseconds(milliseconds(1)).count()
	);
	static constexpr double NANOSECOND_TO_SECONDS = static_cast<double>(
		(double)nanoseconds(1).count() / SECOND_TO_NANOSECONDS
	);
	static constexpr double NANOSECOND_TO_MILISECONDS = static_cast<double>(
		(double)nanoseconds(1).count() / MILISECOND_TO_NANOSECONDS
	);

	extern Time GetCurrentTime();
	extern uint32 GetCurrentTimeRaw();

	extern TimeDetails RawTimeToTimeDetails(const uint32& rawTime);

	extern double NanosecondsToDouble(const nanoseconds durationInNanoseconds);
	extern double UInt32ToDouble(const uint32 durationInNanoseconds);

	extern nanoseconds DoubleToNanoseconds(const double durationInSeconds);
	extern nanoseconds UInt32ToNanoseconds(const uint32 durationInNanoseconds);
	
	extern uint32 DoubleToUInt32(const double durationInSeconds);
	extern uint32 NanosecondsToUInt32(const nanoseconds durationInNanoseconds);
}