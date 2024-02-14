/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "Clock.h"

#include <assert.h>

using std::chrono::duration_cast;

namespace Engine::Common
{
	Clock::Clock() : m_startTime(), m_endTime(), m_isRunning(false) {}
	Clock::~Clock() {}

	bool Clock::IsRunning()
	{
		return m_isRunning;
	}
		
	void Clock::Start()
	{
		m_startTime = Time::GetTimeNow();
		m_isRunning = true;
	}

	void Clock::Stop()
	{
		m_endTime = Time::GetTimeNow();
		m_isRunning = false;
	}

	Time::Duration Clock::GetDuration()
	{
		assert(!m_isRunning);
		assert(!m_startTime.IsZero());
		assert(!m_endTime.IsZero());
		
		return m_endTime - m_startTime;
	}

	Time::TimePoint Clock::GetStartTime()
	{
		return m_startTime;
	}

	Time::TimePoint Clock::GetEndTime()
	{
		return m_endTime;
	}
}