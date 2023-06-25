/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <Common/TimeTypes.h>

namespace Engine::Common::Time
{
	const unsigned int SECOND = 1000;

	static time_point GetCurrentTime();

	static milliseconds AsMilliseconds(const double timeInMilliseconds);
	static nanoseconds AsNanoseconds(milliseconds durationInMilliseconds);
	static nanoseconds AsNanoseconds(const double timeInMilliseconds);

	static const long long DurationToUInt(nanoseconds duration);
	static const long long MillisecondsToUInt(const double timeInMilliseconds);
}