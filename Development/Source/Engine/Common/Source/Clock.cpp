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


	bool Clock::IsRunning()
	{
		return m_isRunning;
	}

	uint32 Clock::GetDuration()
	{
		if (m_startTime == time_point::min())
		{
			// this is bad :c
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
		if(!m_isRunning) m_isRunning = true;
		m_startTime = high_res_clock::now();
	}

	uint32 Clock::GetStartTime()
	{
		return m_startTime.time_since_epoch().count();
	}

	uint32 Clock::GetEndTime()
	{
		return m_endTime.time_since_epoch().count();
	}
}