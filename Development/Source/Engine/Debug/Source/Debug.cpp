/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#ifdef _DEBUG

#include "Debug.h"

#include "TracingFunctionNames.h"

namespace Engine::Debug
{
	namespace Performance
	{

		void PerformanceProfiler::AddFrameStart(const char* const name)
		{
			m_performanceData.frameData[name].push_back(FrameData());
			m_performanceData.frameData[name].back().startTime = Common::GetTimeNow();
		}

		void PerformanceProfiler::AddFrameEnd(const char* const name)
		{
			m_performanceData.frameData[name].back().endTime = Common::GetTimeNow();
		}

		void PerformanceProfiler::IncreaseCounter(const char* const name)
		{
			m_performanceData.frameCounters[name].value++;
		}

		Engine::Debug::Performance::PerformanceData PerformanceProfiler::PopData()
		{
			PerformanceData poppedData = m_performanceData;
			
			ResetData();

			return poppedData;
		}

		void PerformanceProfiler::ResetData()
		{
			// remove all finished frames
			auto isFrameFinished = [](const FrameData& frameData) {
				return frameData.endTime.GetRawTime() != 0;
			};

			for (auto& frameNameToFrameData : m_performanceData.frameData)
			{
				auto& frameDataList = frameNameToFrameData.second;

				auto finishedFrames = std::remove_if(frameDataList.begin(), frameDataList.end(), isFrameFinished);
				frameDataList.erase(finishedFrames, frameDataList.end());
			}

			// reset counters
			m_performanceData.frameCounters.clear();
		}
	}

	DebugManager::DebugManager() :
		m_debugInfoRefreshTime(Common::SECOND_TO_NANOSECONDS),
		m_performanceProfiler(Performance::PerformanceProfiler())
	{

	}

	void DebugManager::StartUp()
	{
		
	}

	void DebugManager::StartDebugManagerClock()
	{
		m_debugUpdateClock.Start();
	}


	Common::Time DebugManager::CalculateAverageFrameDuration(const std::vector<Performance::FrameData>& frameDataList, const size_t frameCounter)
	{
		if (frameCounter < 1)
		{
			ENGINE_WARN("Engine Update Counter is less than 1. Cannot calculate average duration.");
			return Common::Time(0);
		}

		size_t frameDurationSum = 0;
		for (const Performance::FrameData frameData : frameDataList)
		{
			frameDurationSum += (frameData.endTime - frameData.startTime).GetRawTime();
		}

		return Common::Time(frameDurationSum / frameCounter);
	}

	void DebugManager::LogPerformanceInfo(const double deltaTime)
	{
		Performance::PerformanceData performanceData = GetPerformanceProfiler().PopData();

		const size_t engineUpdateCounter = performanceData.frameCounters[sl_Engine_Update].value;
		const size_t renderFrameCounter = performanceData.frameCounters[sl_Engine_RenderFrame].value;

		const std::vector<Performance::FrameData> engineUpdateData = performanceData.frameData[sl_Engine_Update];
		const std::vector<Performance::FrameData> engineRenderFrameData = performanceData.frameData[sl_Engine_RenderFrame];

		Common::Time engineUpdateAvgDuration = CalculateAverageFrameDuration(engineUpdateData, engineUpdateCounter);
		Common::Time renderFrameAvgDuration = CalculateAverageFrameDuration(engineRenderFrameData, renderFrameCounter);
		
		ENGINE_LOG("Frames per Second(FPS): {};\tEngine Updates per Second: {}", renderFrameCounter, engineUpdateCounter);
		ENGINE_LOG("Engine Update ms: {};\t\tRenderFrame ms: {}", engineUpdateAvgDuration.GetMilliseconds(), renderFrameAvgDuration.GetMilliseconds());
		ENGINE_LOG("DeltaTime (seconds): {:.4f}", deltaTime);
	}

	void DebugManager::Update(const double deltaTime)
	{
		if (m_debugUpdateClock.GetDuration() >= m_debugInfoRefreshTime)
		{
			LogPerformanceInfo(deltaTime);
			LogMemoryInfo();

			m_debugUpdateClock.Reset();
		}
	}

	void DebugManager::ShutDown()
	{

	}

	void DebugManager::LogMemoryInfo()
	{

	}
}

#endif // _DEBUG