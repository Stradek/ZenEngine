/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#ifdef _DEBUG

#include <Engine/Core/ISystem.h>

namespace Engine::Debug
{
	namespace Performance
	{
		struct Counter
		{
			Counter() : value(0) {};
			uint32 value;
		};

		struct FrameData
		{
			FrameData() : startTime(0), endTime(0){};

			uint32 startTime;
			uint32 endTime;
		};
		
		class PerformanceProfiler
		{
		private:
			std::unordered_map<std::string, std::vector<FrameData>> m_frameData;
			std::unordered_map<std::string, Counter> m_counters;

		public:
			PerformanceProfiler() {};
			
			void AddFrameStart(const char* const name, uint32 startTime);
			void AddFrameEnd(const char* const name, uint32 endTime);

			void IncreaseCounter(const char* const name);

			void Reset();
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