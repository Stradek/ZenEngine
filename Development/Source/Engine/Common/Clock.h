/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "Defines.h"

#include <chrono>

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

		std::chrono::high_resolution_clock::time_point GetStartTime();
		std::chrono::high_resolution_clock::time_point GetEndTime();

		std::chrono::high_resolution_clock::duration GetDuration();

	private:
		std::chrono::high_resolution_clock::time_point m_startTime;
		std::chrono::high_resolution_clock::time_point m_endTime;

		bool m_isRunning = false;
	};
}