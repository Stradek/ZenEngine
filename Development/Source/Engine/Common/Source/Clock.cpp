/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include <Clock.h>
#include <CommonTime.h>

using std::chrono::duration_cast;

namespace Engine::Common::DateTime
{
	Clock::Clock() : m_startTime(time_point::min()) {}
	Clock::~Clock() {}

	uint32 Clock::GetDuration()
	{
		if (m_startTime == time_point::min())
		{
			__debugbreak();
			// TODO: assert()
			return 0;
		}

		time_point startTimePoint = m_startTime;
		time_point endTimePoint;
		if (m_isRunning)
		{
			endTimePoint = high_res_clock::now();
		}
		else
		{
			endTimePoint = m_endTime;
		}

		auto clockDuration = duration_cast<nanoseconds>(endTimePoint - startTimePoint);
		return NanosecondsToUInt32(clockDuration);
	}

	double Clock::GetDurationAsDouble()
	{
		auto duration = GetDuration();
		return UInt32ToDouble(duration);
	}

	void Clock::Start()
	{
		// TODO: assert(!m_isRunning);
		m_startTime = high_res_clock::now();

		m_isRunning = true;
	}
	void Clock::Stop()
	{
		m_endTime = high_res_clock::now();

		m_isRunning = false;
	}

	void Clock::Reset()
	{
		// TODO: assert(m_isRunning);
		m_startTime = high_res_clock::now();
	}
}