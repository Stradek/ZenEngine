/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "Debug.h"

namespace Engine::Debug
{
	namespace Performance
	{
		PerformanceProfiler::PerformanceProfiler() : m_frameArrayIterator(0)
		{
		}

		void PerformanceProfiler::FrameProfilingStart(std::string functionName)
		{
			time_t timeNow = Common::DateTime::GetCurrentTimeRaw();
			StartFrameData frameData{ timeNow, false };

			std::pair nameToTimePair = { functionName, frameData };
			m_nameToStartFrameData.insert(nameToTimePair);
		}

		void PerformanceProfiler::FrameProfilingEnd(std::string functionName)
		{
			time_t frameFinishTime = Common::DateTime::GetCurrentTimeRaw();
			time_t frameStartTime = m_nameToStartFrameData[functionName].frameStartTime;

			time_t frameDuration = frameFinishTime - frameStartTime;

			FrameData finishedFrameData;
			finishedFrameData.frameStartTime = frameStartTime;
			finishedFrameData.frameFinishTime = frameFinishTime;
			finishedFrameData.frameDuration = frameDuration;

			m_nameToStartFrameData[functionName].isFinished = true;

			m_nameToFrameDataArray[functionName][m_frameArrayIterator] = finishedFrameData;
			m_frameArrayIterator = ++m_frameArrayIterator % maxFrameArrayItems;
		}

		NameToFrameDataArray PerformanceProfiler::GetFrameProfilingData()
		{
			NameToFrameDataArray framesDone;

			for (auto nameEntryIt : m_nameToFrameDataArray)
			{
				FrameDataArray frameDataArray = nameEntryIt.second;

				std::sort(frameDataArray.begin(),
					frameDataArray.end(),
					[](const FrameData& a, const FrameData& b) {
						return a.frameStartTime < b.frameStartTime;
					}
				);

				framesDone[nameEntryIt.first] = frameDataArray;
			}

			return framesDone;
		}

		Engine::Debug::Performance::NameToRawTime PerformanceProfiler::GetAvgFrameProfilingData()
		{
			NameToRawTime nameToAverageTime;
			
			NameToFrameDataArray nameToFrameDataArray = GetFrameProfilingData();
			for (auto nameEntryIt : nameToFrameDataArray)
			{
				FrameDataArray frameDataArray = nameEntryIt.second;
				const uint framesCount = frameDataArray.size();
				const uint lastElementIndex = framesCount - 1;

				time_t framesAccumulatedDuration = std::accumulate(frameDataArray.begin(), frameDataArray.end(), 0.0,
					[](time_t accumulator, const FrameData& frameData)
					{
						return accumulator + frameData.frameDuration;
					}
				);

				time_t averageFrameTime = framesAccumulatedDuration / framesCount;

				nameToAverageTime[nameEntryIt.first] = averageFrameTime;
			}

			return nameToAverageTime;
		}

	}

	void DebugManager::StartUp()
	{
		m_performanceProfiler = Performance::PerformanceProfiler();
	}

	void DebugManager::ShutDown()
	{

	}
}
