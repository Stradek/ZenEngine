/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include <Common/Time.h>

using std::chrono::duration_cast;

namespace Engine::Common::Time
{
	static time_point GetCurrentTime()
	{
		return high_res_clock::now();
	}

	static milliseconds AsMilliseconds(const double timeInMilliseconds)
	{
		milliseconds durationInMilliseconds = duration_cast<milliseconds>(
			millisecond_duration(timeInMilliseconds)
		);

		return durationInMilliseconds;
	}

	static nanoseconds AsNanoseconds(milliseconds durationInMilliseconds)
	{
		nanoseconds durationInNanoseconds = durationInMilliseconds;
		return durationInNanoseconds;
	}

	static nanoseconds AsNanoseconds(const double timeInMilliseconds)
	{
		nanoseconds durationInNanoseconds = AsMilliseconds(timeInMilliseconds);

		return durationInNanoseconds;
	}

	static const long long DurationToUInt(nanoseconds duration)
	{
		return duration.count();
	}

	static const long long MillisecondsToUInt(const double timeInMilliseconds)
	{
		nanoseconds durationInNanoseconds = AsNanoseconds(timeInMilliseconds);
		return durationInNanoseconds.count();
	}
}