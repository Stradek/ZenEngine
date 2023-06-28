/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include <CommonTime.h>

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

namespace Engine::Common::Time
{
	const uint32 ONE_SECOND = 1;

	const uint32 SECOND_TO_NANOSECOND_RATIO = static_cast<uint32>(
		nanoseconds(seconds(1)).count()
	);

	const uint32 MILLISECOND_TO_NANOSECOND_RATIO = static_cast<uint32>(
		nanoseconds(milliseconds(1)).count()
	);


	const double NANOSECOND_TO_SECOND_RATIO = static_cast<double>(
		(double) nanoseconds(1).count() / SECOND_TO_NANOSECOND_RATIO
	);

	extern const double NANOSECOND_TO_MILLISECOND_RATIO = static_cast<double>(
		(double) nanoseconds(1).count() / MILLISECOND_TO_NANOSECOND_RATIO
	);


	time_point GetCurrentTime()
{
		return high_res_clock::now();
	}

	/*
		To Double
	*/

	double NanosecondsToDouble(const nanoseconds durationInNanoseconds)
	{
		const uint32 durationInNanoseconds_uint32 = NanosecondsToUInt32(durationInNanoseconds);
		const double durationInSeconds = UInt32ToDouble(durationInNanoseconds_uint32);
		return durationInSeconds;
	}

	double UInt32ToDouble(const uint32 durationInNanoseconds)
	{
		const double durationInSeconds = static_cast<double>(
			durationInNanoseconds * NANOSECOND_TO_SECOND_RATIO
		);

		return durationInSeconds;
	}

	/*
		To Nanoseconds
	*/

	nanoseconds DoubleToNanoseconds(const double durationInSeconds)
	{
		const uint32 durationInUInt32 = DoubleToUInt32(durationInSeconds);
		const nanoseconds durationInNanoseconds = UInt32ToNanoseconds(durationInUInt32);
		return durationInNanoseconds;
	}

	nanoseconds UInt32ToNanoseconds(const uint32 durationInUInt32)
	{
		const nanoseconds durationInNanoseconds = nanoseconds_duration_from_uint32(
			durationInUInt32
		);

		return durationInNanoseconds;
	}

	/*
		To UInt32
	*/

	uint32 DoubleToUInt32(const double durationInSeconds)
	{
		const nanoseconds durationInNanoseconds = duration_cast<nanoseconds>(
			seconds_duration_from_double(durationInSeconds)
		);

		const auto duration = NanosecondsToUInt32(durationInNanoseconds);
		return static_cast<uint32>(duration);
	}

	uint32 NanosecondsToUInt32(const nanoseconds durationInNanoseconds)
	{
		const auto duration = durationInNanoseconds.count();
		return static_cast<uint32>(duration);
	}
}