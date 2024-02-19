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

namespace Engine::Common
{
	static constexpr size_t HOUR_TO_NANOSECONDS = nanoseconds(hours(1)).count();
	static constexpr size_t MINUTE_TO_NANOSECONDS = nanoseconds(minutes(1)).count();
	static constexpr size_t SECOND_TO_NANOSECONDS = nanoseconds(seconds(1)).count();
	static constexpr size_t MILISECOND_TO_NANOSECONDS = nanoseconds(milliseconds(1)).count();

	static constexpr double NANOSECOND_TO_HOUR = 1.0 / HOUR_TO_NANOSECONDS;
	static constexpr double NANOSECOND_TO_MINUTE = 1.0 / MINUTE_TO_NANOSECONDS;
	static constexpr double NANOSECOND_TO_SECOND = 1.0 / SECOND_TO_NANOSECONDS;
	static constexpr double NANOSECOND_TO_MILLISECOND = 1.0 / MILISECOND_TO_NANOSECONDS;
}