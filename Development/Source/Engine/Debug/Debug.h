/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#ifdef _DEBUG

#include "Core/ISystem.h"

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
			Engine::Common::Time::TimePoint startTime{};
			Engine::Common::Time::TimePoint endTime{};

			bool IsValid() const { return startTime != Engine::Common::Time::TimePoint::min(); };
		};

		struct PerformanceData
		{
			std::unordered_map<std::string, std::vector<FrameData>> frameData;
			std::unordered_map<std::string, Counter> frameCounters;
		};
		
		class PerformanceProfiler
		{
		public:
			PerformanceProfiler() {};
			
			void AddFrameStart(const char* const name);
			void AddFrameEnd(const char* const name);
			void IncreaseCounter(const char* const name);

			PerformanceData PopData();
		private:
			PerformanceData m_performanceData;
			std::unordered_map<std::string, FrameData> m_frameDataInProgress;
			
			bool IsFrameFinished(const FrameData& frameData) const;

			PerformanceData GetPerformanceData();
			void ResetFinishedData();
		};
	}

	class DebugManager : Engine::Core::ISystem
	{
	public:
		DebugManager();

		Performance::PerformanceProfiler& GetPerformanceProfiler() { return m_performanceProfiler; };

		void StartUp() override;
		void ShutDown() override;
		
		void Update(const double deltaTime) override;
		
		void StartDebugManagerClock();
	private:
		Performance::PerformanceProfiler m_performanceProfiler;

		const std::chrono::high_resolution_clock::duration m_debugInfoRefreshTime;
		Common::Clock m_debugUpdateClock;

		void LogPerformanceInfo(const double deltaTime);
		void LogMemoryInfo();

		Common::Time::Duration CalculateAverageFrameDuration(const std::vector<Performance::FrameData>& frameDataList, const size_t frameCounter);
	};
}

#endif // _DEBUG