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

	}

	DebugManager::DebugManager() :
		m_debugInfoUpdateFrequency(Common::DateTime::Time(Common::DateTime::SECOND_TO_NANOSECONDS)),
		m_shouldLogStats(false),
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

	void DebugManager::LogProfilingInfo(const uint32 deltaTime)
	{
		// TODO: 
		// - Get Counters value from Performance Profiler (RenderFrame, Update, etc.)
		// - Get Average Duration from Performance Profiler (RenderFrame, Update, etc.)

		double deltaTimeMiliseconds = deltaTime * Common::DateTime::NANOSECOND_TO_MILISECONDS;

		ENGINE_LOG("[FPS: {}] Game Update ms: {}; Render ms: {}; DeltaTime ms: {:.4f}", -1, -1, -1, deltaTimeMiliseconds);
		ENGINE_LOG("          Game Updates per Second: {}", -1);
		ENGINE_WARN("Counters and average duration for Profiling Info not implemented.");
	}

	void DebugManager::Update(const uint32 deltaTime)
	{
		if(m_shouldLogStats)
		{
			
			LogProfilingInfo(deltaTime);
			LogMemoryInfo();

			m_shouldLogStats = false;
		}

		if (m_debugUpdateClock.GetDuration() >= m_debugInfoUpdateFrequency.GetTimeRaw())
		{
			m_shouldLogStats = true;
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