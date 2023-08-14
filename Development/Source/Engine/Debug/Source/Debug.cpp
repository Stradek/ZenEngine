/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#ifdef _DEBUG

#include "Debug.h"

#include <Core/Log.h>

namespace Engine::Debug
{
	namespace Performance
	{
		PerformanceProfiler::PerformanceProfiler()
		{
		}

		void PerformanceProfiler::FrameProfilingStart(std::string functionName)
		{
			ENGINE_ASSERT(m_nameToStartFrameData.count(functionName) == 0, ("Frame {} didn't finish and still exists as startFrameData entry. Missing FrameProfilingEnd call.", functionName))

			uint32 timeNow = Common::DateTime::GetCurrentTimeRaw();
			StartFrameData frameData{ timeNow, false };

			m_nameToStartFrameData[functionName] = frameData;
		}

		void PerformanceProfiler::FrameProfilingEnd(std::string functionName)
		{
			uint32 frameFinishTime = Common::DateTime::GetCurrentTimeRaw();
			uint32 frameStartTime = m_nameToStartFrameData[functionName].startTime;
			uint32 frameDuration = frameFinishTime - frameStartTime;

			FrameData finishedFrameData;
			finishedFrameData.startTime = frameStartTime;
			finishedFrameData.endTime = frameFinishTime;
			finishedFrameData.duration = frameDuration;

			m_nameToStartFrameData.erase(functionName);

			// create new buffer, if there is none for this function name
			m_nameToFrameDataCircularBuffer[functionName].EmplaceBack(finishedFrameData);
		}

		NameToFrameDataBuffer PerformanceProfiler::GetFrameProfilingData()
		{
			NameToFrameDataBuffer framesDone;

			for (auto nameEntryIt : m_nameToFrameDataCircularBuffer)
			{
				FrameDataBuffer frameDataBuffer = nameEntryIt.second.GetAll();

				std::sort(frameDataBuffer.begin(),
					frameDataBuffer.end(),
					[](const FrameData& a, const FrameData& b) {
						return a.startTime > b.startTime;
					}
				);

				framesDone[nameEntryIt.first] = frameDataBuffer;
			}

			return framesDone;
		}

		NameToRawTime PerformanceProfiler::GetAvgFrameProfilingData()
		{
			NameToRawTime nameToAverageTime;
			
			NameToFrameDataBuffer nameToFrameDataBuffer = GetFrameProfilingData();
			for (auto nameEntryIt : nameToFrameDataBuffer)
			{
				FrameDataBuffer frameDataBuffer = nameEntryIt.second;
				const uint framesCount = frameDataBuffer.size();
				const uint lastElementIndex = framesCount - 1;

				uint32 framesAccumulatedDuration = std::accumulate(frameDataBuffer.begin(), frameDataBuffer.end(), 0.0,
					[](uint32 accumulator, const FrameData& frameData)
					{
						return accumulator + frameData.duration;
					}
				);

				uint32 averageFrameTime = framesAccumulatedDuration / framesCount;

				nameToAverageTime[nameEntryIt.first] = averageFrameTime;
			}

			return nameToAverageTime;
		}
	}

	void DebugManager::StartUp()
	{
		m_performanceProfiler = Performance::PerformanceProfiler();

		ClearEngineCounters();
		m_debugUpdateClock.Start();
	}

	void DebugManager::ClearEngineCounters()
	{
		m_engineUpdatesLastSecondCounter = m_currentSecondUpdatesCount;
		m_renderedFramesLastSecondCounter = m_currentSecondRenderFramesCount;

		m_currentSecondUpdatesCount = 0;
		m_currentSecondRenderFramesCount = 0;

	}

	void DebugManager::Update(const uint32 deltaTime)
	{
		if(m_shouldLogStats)
		{
			Performance::NameToRawTime m_profiledFunctionNameToAvgDuration = GetPerformanceProfiler().GetAvgFrameProfilingData();

			uint32 engineUpdateTimeRaw = m_profiledFunctionNameToAvgDuration[sl_Engine_Update];
			uint32 engineRenderFrameTimeRaw = m_profiledFunctionNameToAvgDuration[sl_Engine_RenderFrame];

			double engineUpdateTime = Common::DateTime::UInt32ToDouble(engineUpdateTimeRaw);
			double engineRenderFrameTime = Common::DateTime::UInt32ToDouble(engineRenderFrameTimeRaw);
			
			double deltaTimeMiliseconds = deltaTime * Common::DateTime::NANOSECOND_TO_MILISECONDS;

			ENGINE_LOG("[FPS: {}] Game Update ms: {:.4f}; Render ms: {:.4f}; DeltaTime ms: {:.4f}", m_renderedFramesLastSecondCounter, engineUpdateTime, engineRenderFrameTime, deltaTimeMiliseconds);
			ENGINE_LOG("          Game Updates per Second: {}; Render Updates per Second: {}", m_engineUpdatesLastSecondCounter, m_renderedFramesLastSecondCounter);
			m_shouldLogStats = false;
		}

		if (m_debugUpdateClock.GetDuration() >= m_debugInfoUpdateFrequency.GetTimeRaw())
		{
			ClearEngineCounters();
			m_shouldLogStats = true;

			m_debugUpdateClock.Reset();
		}

	}

	void DebugManager::ShutDown()
	{

	}

	void DebugManager::AddToUpdateCounter()
	{
		++m_currentSecondUpdatesCount;
	}

	void DebugManager::AddToRenderFrameCounter()
	{
		++m_currentSecondRenderFramesCount;
	}

}

#endif // _DEBUG