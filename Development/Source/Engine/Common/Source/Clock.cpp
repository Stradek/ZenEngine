/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "Clock.h"
#include "CommonTime.h"

#include <assert.h>

using std::chrono::duration_cast;

namespace Engine::Common
{
	Clock::Clock() : m_startTime(0), m_endTime(0), m_isRunning(false) {}
	Clock::~Clock() {}

	bool Clock::IsRunning()
	{
		return m_isRunning;
	}

	Time Clock::GetDuration()
	{
		assert(m_isRunning);
		
		m_endTime = GetTimeNow();
		return Time::Duration(m_startTime, m_endTime);
	}

	void Clock::Start()
	{
		m_startTime = GetTimeNow();
		m_isRunning = true;
	}
	void Clock::Stop()
	{
		m_endTime = GetTimeNow();
		m_isRunning = false;
	}

	void Clock::Reset()
	{
		m_startTime = GetTimeNow();
	}

	Time Clock::GetStartTime()
	{
		return m_startTime;
	}

	Time Clock::GetEndTime()
	{
		return m_endTime;
	}
}