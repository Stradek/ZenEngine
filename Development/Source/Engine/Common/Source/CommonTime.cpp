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

namespace Engine::Common::DateTime
{
	TimeDetails Time::GetTime() const
	{
		const uint32 rawTime = GetTimeRaw();
		const TimeDetails timeDetails = RawTimeToTimeDetails(rawTime);

		return timeDetails;
	}

	uint32 Time::GetTimeRaw() const
	{
		return m_rawTime;
	};


	Time GetCurrentTime()
	{
		uint32 rawTime = GetCurrentTimeRaw();

		Time currentTime = Time(rawTime);
		return currentTime;
	}

	extern uint32 GetCurrentTimeRaw()
	{
		uint32 rawTimeNow = high_res_clock::now().time_since_epoch().count();
		return rawTimeNow;
	}


	extern TimeDetails RawTimeToTimeDetails(const uint32& rawTime)
	{
		uint32 rawTimeToMove = const_cast<uint32&>(rawTime);
		TimeDetails timeDetails;

		uint hoursInRawTime = floor(rawTimeToMove / HOUR_TO_NANOSECONDS);
		rawTimeToMove -= hoursInRawTime * HOUR_TO_NANOSECONDS;

		uint minutesInRawTime = floor(rawTimeToMove / MINUTE_TO_NANOSECONDS);
		rawTimeToMove -= minutesInRawTime * MINUTE_TO_NANOSECONDS;

		uint secondsInRawTime = floor(rawTimeToMove / SECOND_TO_NANOSECONDS);
		rawTimeToMove -= secondsInRawTime * SECOND_TO_NANOSECONDS;

		uint milisecondsInRawTime = floor(rawTimeToMove / MILISECOND_TO_NANOSECONDS);
		rawTimeToMove -= milisecondsInRawTime * MILISECOND_TO_NANOSECONDS;

		uint nanosecondsInRawTime = rawTimeToMove;

		timeDetails.hours = hoursInRawTime;
		timeDetails.minutes = minutesInRawTime;
		timeDetails.seconds = secondsInRawTime;
		timeDetails.miliseconds = milisecondsInRawTime;
		timeDetails.nanoseconds = nanosecondsInRawTime;

		return timeDetails;
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
			durationInNanoseconds * NANOSECOND_TO_SECONDS
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