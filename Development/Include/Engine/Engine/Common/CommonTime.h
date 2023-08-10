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
	struct Time
	{
		int hour;
		int minute;
		int second;
	};

	static constexpr uint32 ONE_SECOND = 1;
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
	extern time_t GetCurrentTimeRaw();

	extern double NanosecondsToDouble(const nanoseconds durationInNanoseconds);
	extern double UInt32ToDouble(const uint32 durationInNanoseconds);

	extern nanoseconds DoubleToNanoseconds(const double durationInSeconds);
	extern nanoseconds UInt32ToNanoseconds(const uint32 durationInNanoseconds);
	
	extern uint32 DoubleToUInt32(const double durationInSeconds);
	extern uint32 NanosecondsToUInt32(const nanoseconds durationInNanoseconds);
}