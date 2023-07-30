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
	static constexpr uint32 NANOSECONDS_IN_SECOND = static_cast<uint32>(
		nanoseconds(seconds(1)).count()
	);
	static constexpr uint32 NANOSECONDS_IN_MILISECOND = static_cast<uint32>(
		nanoseconds(milliseconds(1)).count()
	);
	static constexpr double SECONDS_IN_NANOSECOND = static_cast<double>(
		(double)nanoseconds(1).count() / NANOSECONDS_IN_SECOND
	);
	static constexpr double MILISECONDS_IN_NANOSECOND = static_cast<double>(
		(double)nanoseconds(1).count() / NANOSECONDS_IN_MILISECOND
	);

	extern Time GetCurrentTime(); 

	extern double NanosecondsToDouble(const nanoseconds durationInNanoseconds);
	extern double UInt32ToDouble(const uint32 durationInNanoseconds);

	extern nanoseconds DoubleToNanoseconds(const double durationInSeconds);
	extern nanoseconds UInt32ToNanoseconds(const uint32 durationInNanoseconds);
	
	extern uint32 DoubleToUInt32(const double durationInSeconds);
	extern uint32 NanosecondsToUInt32(const nanoseconds durationInNanoseconds);
}