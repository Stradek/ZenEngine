/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#ifdef _DEBUG

#include "Engine/Core/ISystem.h"

namespace Engine::Debug
{
	namespace Performance
	{
		struct Counter
		{
			size_t value = 0;
		};

		struct FrameData
		{
			Common::Time startTime = 0;
			Common::Time endTime = 0;
		};

		struct PerformanceData
		{
			std::unordered_map<std::string, std::vector<FrameData>> frameData;
			std::unordered_map<std::string, Counter> frameCounters;
		};
		
		class PerformanceProfiler
		{
		private:
			PerformanceData m_performanceData;

			void ResetData();
		public:
			PerformanceProfiler() {};
			
			void AddFrameStart(const char* const name);
			void AddFrameEnd(const char* const name);

			void IncreaseCounter(const char* const name);

			PerformanceData PopData();
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

		void Update(const double deltaTime) override;

	private:
		Performance::PerformanceProfiler m_performanceProfiler;

		const Common::Time m_debugInfoRefreshTime;
		Common::Clock m_debugUpdateClock;
		bool m_shouldLogStats;

		void LogPerformanceInfo(const double deltaTime);
		void LogMemoryInfo();

		Common::Time CalculateAverageFrameDuration(const std::vector<Performance::FrameData>& frameDataList, const size_t frameCounter);
	};
}

#endif // _DEBUG