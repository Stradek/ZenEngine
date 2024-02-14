/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "Defines.h"
#include "CommonTime.h"

namespace Engine::Common
{
	class Clock
	{
	public:
		Clock();
		~Clock();

		bool IsRunning();

		void Start();
		void Stop();

		Time::Duration GetDuration();
		Time::TimePoint GetStartTime();
		Time::TimePoint GetEndTime();

	private:
		bool m_isRunning = false;

		Time::TimePoint m_startTime;
		Time::TimePoint m_endTime;
	};
}