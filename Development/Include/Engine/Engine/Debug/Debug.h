/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#ifdef _DEBUG

#include <Engine/Core/ISystem.h>

namespace Engine::Debug
{
	enum CounterType
	{
		CounterRaw,
		CounterPerSecond
	};

	namespace Performance
	{
		struct StartFrameData
		{
			uint32 startTime;
			bool isFinished = false;
		};

		struct FrameData
		{
			FrameData() : startTime(0), endTime(0), duration(0) {};

			uint32 startTime;
			uint32 endTime;
			uint32 duration;
		};
		
		class PerformanceProfiler
		{
		public:
			PerformanceProfiler() {};
		};
	}

	using PerformanceProfilerRef = Performance::PerformanceProfiler&;

	class DebugManager : Engine::Core::ISystem
	{
	public:
		DebugManager();

		void StartUp() override;
		void ShutDown() override;

		Performance::PerformanceProfiler& GetPerformanceProfiler() { return m_performanceProfiler; };

		void StartDebugManagerClock();

		void Update(const uint32 deltaTime) override;

	private:
		Performance::PerformanceProfiler m_performanceProfiler;

		const Common::DateTime::Time m_debugInfoUpdateFrequency;
		Common::DateTime::Clock m_debugUpdateClock;
		bool m_shouldLogStats;

		void LogProfilingInfo(const uint32 deltaTime);
		void LogMemoryInfo();
	};
}

#endif // _DEBUG