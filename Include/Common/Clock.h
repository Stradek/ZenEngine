/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <Common/TimeTypes.h>

namespace Engine::Common::Time
{
	class Clock
	{
	public:
		Clock();
		~Clock();

		const nanoseconds GetDuration();
		const double GetDurationAsDouble();

		void Start();
		void Stop();
		void Reset();

	private:
		time_point m_startTime = time_point::min();
		time_point m_endTime;

		bool m_isRunning = false;
	};
}