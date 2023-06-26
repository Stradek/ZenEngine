/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <TimeTypes.h>

/*
	NOTE:
	Seconds are used as a default value for double.
	Nanoseconds are used as a default value for engine computations.
	UInt32 is raw representation of Nanoseconds.
*/

namespace Engine::Common::Time
{
	extern const uint32 ONE_SECOND;
	extern const uint32 SECOND_TO_NANOSECOND_RATIO;
	extern const uint32 MILLISECOND_TO_NANOSECOND_RATIO;
	extern const double NANOSECOND_TO_SECOND_RATIO;
	extern const double NANOSECOND_TO_MILLISECOND_RATIO;

	extern time_point GetCurrentTime();

	extern double NanosecondsToDouble(const nanoseconds durationInNanoseconds);
	extern double UInt32ToDouble(const uint32 durationInNanoseconds);

	extern nanoseconds DoubleToNanoseconds(const double durationInSeconds);
	extern nanoseconds UInt32ToNanoseconds(const uint32 durationInNanoseconds);
	
	extern uint32 DoubleToUInt32(const double durationInSeconds);
	extern uint32 NanosecondsToUInt32(const nanoseconds durationInNanoseconds);
}