/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <Defines.h>
#include <TimeTypes.h>

namespace Engine::Common::Time
{
	class Clock
	{
	public:
		Clock();
		~Clock();

		uint32 GetDuration();
		double GetDurationAsDouble();

		void Start();
		void Stop();
		void Reset();

	private:
		time_point m_startTime = time_point::min(); // move initialization to cpp file
		time_point m_endTime;

		bool m_isRunning = false;
	};
}