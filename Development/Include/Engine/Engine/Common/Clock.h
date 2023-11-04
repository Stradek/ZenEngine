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
		void Reset();

		Time GetStartTime();
		Time GetEndTime();

		Time GetDuration();

	private:
		Time m_startTime;
		Time m_endTime;

		bool m_isRunning = false;
	};
}