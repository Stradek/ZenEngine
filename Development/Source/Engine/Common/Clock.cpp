/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "Clock.h"
#include "CommonTime.h"

#include <assert.h>

namespace Engine::Common
{
	Clock::Clock() : m_isRunning(false) {}
	Clock::~Clock() {}

	bool Clock::IsRunning()
	{
		return m_isRunning;
	}

	void Clock::Start()
	{
		m_startTime = std::chrono::high_resolution_clock::now();
		m_isRunning = true;
	}
	void Clock::Stop()
	{
		m_endTime = std::chrono::high_resolution_clock::now();
		m_isRunning = false;
	}

	void Clock::Reset()
	{
		m_startTime = std::chrono::high_resolution_clock::now();
	}

	std::chrono::high_resolution_clock::time_point Clock::GetStartTime()
	{
		return m_startTime;
	}

	std::chrono::high_resolution_clock::time_point Clock::GetEndTime()
	{
		return m_endTime;
	}

	std::chrono::high_resolution_clock::duration Clock::GetDuration()
	{
		assert(m_isRunning);

		m_endTime = std::chrono::high_resolution_clock::now();
		return m_startTime - m_endTime;
	}
}