/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <Common/TimeTypes.h>

namespace Engine::Common::Time
{
	// TODO: 
	// I should probably move every millisecond
	// reference except strings to nanoseconds implementation
	// but still return milliseconds as strings

	// second as milliseconds. 
	const unsigned int SECOND_IN_MILLISECONDS = 1000;

	static time_point GetCurrentTime();

	static milliseconds AsMilliseconds(const double timeInMilliseconds);
	static nanoseconds AsNanoseconds(milliseconds durationInMilliseconds);
	static nanoseconds AsNanoseconds(const double timeInMilliseconds);

	static const long long DurationToUInt(nanoseconds duration);
	static const long long MillisecondsToUInt(const double timeInMilliseconds);
}