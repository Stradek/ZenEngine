/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include <Clock.h>
#include <CommonTime.h>

#include <assert.h>

using std::chrono::duration_cast;

namespace Engine::Common::DateTime
{
	Clock::Clock() : m_startTime(0), m_endTime(0), m_isRunning(false) {}
	Clock::~Clock() {}

	bool Clock::IsRunning()
	{
		return m_isRunning;
	}

	uint32 Clock::GetDuration()
	{
		assert(m_startTime != 0);
		
		uint32 endTime;
		if (m_isRunning)
		{
			endTime = DateTime::GetTimeRaw();
		}
		else
		{
			assert(m_endTime != 0);
			endTime = m_endTime;
		}

		uint32 clockDuration = endTime - m_startTime;
		return clockDuration;
	}

	double Clock::GetDurationAsDouble()
	{
		auto duration = GetDuration();
		return UInt32ToDouble(duration);
	}

	void Clock::Start()
	{
		m_startTime = DateTime::GetTimeRaw();
		m_isRunning = true;
	}
	void Clock::Stop()
	{
		m_endTime = DateTime::GetTimeRaw();
		m_isRunning = false;
	}

	void Clock::Reset()
	{
		if(!m_isRunning) m_isRunning = true;
		m_startTime = DateTime::GetTimeRaw();
	}

	uint32 Clock::GetStartTime()
	{
		return m_startTime;
	}

	uint32 Clock::GetEndTime()
	{
		return m_endTime;
	}
}