/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#ifdef _DEBUG

#include "Debug.h"

#include <TracingFunctionNames.h>

namespace Engine::Debug
{
	namespace Performance
	{
		PerformanceProfiler::PerformanceProfiler() :
			m_nameToStartFrameData(std::make_unique<NameToStartFrameData>()), 
			m_nameToFrameDataCircularBuffer(std::make_unique<NameToFrameDataCircularBuffer>()),
			m_nameToCounterRaw(std::make_shared<NameToCounter>()),
			m_nameToCounterLastSecond(std::make_shared<NameToCounter>()),
			m_nameToCounterPerSecond(std::make_shared<NameToCounter>())
		{

		}

		void PerformanceProfiler::UpdateCounterPerSecond()
		{
			for (auto& counterEntryIt : *m_nameToCounterRaw)
			{
				auto& counterName = counterEntryIt.first;
				auto& counterValue = counterEntryIt.second;

				(*m_nameToCounterPerSecond)[counterName] = counterValue - (*m_nameToCounterLastSecond)[counterName];
				(*m_nameToCounterLastSecond)[counterName] = counterValue;
			}
		}

		void PerformanceProfiler::IncrementCounter(std::string functionName, uint32 count)
		{
			(*m_nameToCounterRaw)[functionName] += count;
		}

		uint32 PerformanceProfiler::GetCounterValue(CounterType counterType, std::string functionName)
		{
			std::unique_ptr<std::shared_ptr<NameToCounter>> counterPtr;
			switch (counterType)
			{
			case CounterRaw:
				counterPtr = std::make_unique<std::shared_ptr<NameToCounter>>(m_nameToCounterRaw);
				break;
			case CounterPerSecond:
				counterPtr = std::make_unique<std::shared_ptr<NameToCounter>>(m_nameToCounterPerSecond);
				break;
			}

			uint32 counterInstances = (*counterPtr)->count(functionName);
			bool counterExists = counterInstances > 0;
			ENGINE_ASSERT(counterExists, "Counter for given function name doesn't exist.");

			if (counterExists)
			{
				return (*counterPtr)->at(functionName);
			}
			else
			{
				return -1;
			}
		}

		void PerformanceProfiler::FrameProfilingStart(std::string functionName)
		{
			ENGINE_ASSERT(m_nameToStartFrameData->count(functionName) == 0, "Frame {} didn't finish and still exists as startFrameData entry. Missing FrameProfilingEnd call.", functionName)

			uint32 timeNow = Common::DateTime::GetCurrentTimeRaw();
			StartFrameData frameData{ timeNow, false };

			(*m_nameToStartFrameData)[functionName] = frameData;
		}

		void PerformanceProfiler::FrameProfilingEnd(std::string functionName)
		{
			uint32 frameFinishTime = Common::DateTime::GetCurrentTimeRaw();
			uint32 frameStartTime = (*m_nameToStartFrameData)[functionName].startTime;
			uint32 frameDuration = frameFinishTime - frameStartTime;

			FrameData finishedFrameData;
			finishedFrameData.startTime = frameStartTime;
			finishedFrameData.endTime = frameFinishTime;
			finishedFrameData.duration = frameDuration;

			m_nameToStartFrameData->erase(functionName);

			// create new buffer, if there is none for this function name
			(*m_nameToFrameDataCircularBuffer)[functionName].EmplaceBack(finishedFrameData);
		}

		NameToFrameDataBuffer PerformanceProfiler::GetFrameProfilingData()
		{
			NameToFrameDataBuffer framesDone;

			for (auto frameDataCircularBufferIt : *m_nameToFrameDataCircularBuffer)
			{
				auto& frameDataName = frameDataCircularBufferIt.first;
				auto& frameDataValue = frameDataCircularBufferIt.second;

				FrameDataBuffer frameDataBuffer = frameDataValue.GetAll();

				std::sort(frameDataBuffer.begin(),
					frameDataBuffer.end(),
					[](const FrameData& a, const FrameData& b) {
						return a.startTime > b.startTime;
					}
				);

				framesDone[frameDataName] = frameDataBuffer;
			}

			return framesDone;
		}

		NameToRawTime PerformanceProfiler::GetAvgFrameTimingData()
		{
			NameToRawTime nameToAverageTime;
			
			NameToFrameDataBuffer nameToFrameDataBuffer = GetFrameProfilingData();
			for (auto frameDataBufferIt : nameToFrameDataBuffer)
			{
				auto& frameDataBufferName = frameDataBufferIt.first;
				auto& frameDataBufferValue = frameDataBufferIt.second;

				FrameDataBuffer frameDataBuffer = frameDataBufferValue;
				const uint framesCount = frameDataBuffer.size();
				const uint lastElementIndex = framesCount - 1;

				uint32 framesAccumulatedDuration = std::accumulate(frameDataBuffer.begin(), frameDataBuffer.end(), 0.0,
					[](uint32 accumulator, const FrameData& frameData)
					{
						return accumulator + frameData.duration;
					}
				);

				uint32 averageFrameTime = framesAccumulatedDuration / framesCount;

				nameToAverageTime[frameDataBufferName] = averageFrameTime;
			}

			return nameToAverageTime;
		}
	}

	DebugManager::DebugManager() :
		m_debugInfoUpdateFrequency(Common::DateTime::Time(Common::DateTime::SECOND_TO_NANOSECONDS)),
		m_shouldLogStats(false),
		m_performanceProfiler(std::make_shared<Performance::PerformanceProfiler>())
	{

	}

	void DebugManager::StartUp()
	{
		
	}

	void DebugManager::StartPerformanceProfiler()
	{
		ClearEngineCounters();
		m_debugUpdateClock.Start();
	}

	void DebugManager::ClearEngineCounters()
	{

	}

	void DebugManager::Update(const uint32 deltaTime)
	{
		if(m_shouldLogStats)
		{
			Performance::NameToRawTime m_profiledFunctionNameToAvgDuration = GetPerformanceProfiler()->GetAvgFrameTimingData();

			uint32 renderedFramesPerSecond = GetPerformanceProfiler()->GetCounterValue(CounterType::CounterPerSecond, sl_Engine_RenderFrame);
			uint32 engineUpdatesPerSecond = GetPerformanceProfiler()->GetCounterValue(CounterType::CounterPerSecond, sl_Engine_Update);

			uint32 engineUpdateTimeRaw = m_profiledFunctionNameToAvgDuration[sl_Engine_Update];
			uint32 engineRenderFrameTimeRaw = m_profiledFunctionNameToAvgDuration[sl_Engine_RenderFrame];

			double engineUpdateTime = Common::DateTime::UInt32ToDouble(engineUpdateTimeRaw);
			double engineRenderFrameTime = Common::DateTime::UInt32ToDouble(engineRenderFrameTimeRaw);
			
			double deltaTimeMiliseconds = deltaTime * Common::DateTime::NANOSECOND_TO_MILISECONDS;

			ENGINE_LOG("[FPS: {}] Game Update ms: {:.4f}; Render ms: {:.4f}; DeltaTime ms: {:.4f}", renderedFramesPerSecond, engineUpdateTime, engineRenderFrameTime, deltaTimeMiliseconds);
			ENGINE_LOG("          Game Updates per Second: {}", engineUpdatesPerSecond);
			m_shouldLogStats = false;
		}

		if (m_debugUpdateClock.GetDuration() >= m_debugInfoUpdateFrequency.GetTimeRaw())
		{
			GetPerformanceProfiler()->UpdateCounterPerSecond();
			m_shouldLogStats = true;

			m_debugUpdateClock.Reset();
		}

	}

	void DebugManager::ShutDown()
	{

	}
}

#endif // _DEBUG