/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "GameEngine.h"

#include <IEngineApplication.h>
#include <Debug/Debug.h>

#include <tracy/Tracy.hpp>

namespace Engine
{
	void GameEngine::Run(std::unique_ptr<IEngineApplication> appInstance)
	{
		GameEngine engineInstance = GameEngine(std::move(appInstance));
		engineInstance.EngineRun();

		engineInstance.ShutDown();
	}

	GameEngine::GameEngine(std::unique_ptr<IEngineApplication> appInstance) :
		m_appInstance(std::move(appInstance))
	{
		Core::Log::Init();

		StartUp();

	}

	void GameEngine::StartUp()
	{
#ifdef _DEBUG
		m_debugManager.StartUp();
#endif


		m_appInstance->StartUp();
	}

	void GameEngine::Update()
	{
		ENGINE_FRAME_MARK_START(sl_Engine_Update);

#ifdef _DEBUG
		if (m_debugUpdateQueue > 0)
		{
			m_profiledFunctionNameToAvgDuration = m_debugManager.GetPerformanceProfiler().GetAvgFrameProfilingData();
			double deltaTime = m_deltaTime * Common::DateTime::NANOSECOND_TO_MILISECONDS;
			
			time_t engineUpdateTimeRaw = m_profiledFunctionNameToAvgDuration[sl_Engine_Update];
			time_t engineRenderFrameTimeRaw = m_profiledFunctionNameToAvgDuration[sl_Engine_RenderFrame];

			double engineUpdateTime = Common::DateTime::UInt32ToDouble(engineUpdateTimeRaw);
			double engineRenderFrameTime = Common::DateTime::UInt32ToDouble(engineRenderFrameTimeRaw);

			ENGINE_LOG("[FPS: {}] Game Update ms: {:.4f}; Render ms: {:.4f}; DeltaTime ms: {:.4f}", m_renderedFramesLastSecondCounter, engineUpdateTime, engineRenderFrameTime, deltaTime);
			ENGINE_LOG("          Game Updates per Second: {}; Render Updates per Second: {}", m_engineUpdatesLastSecondCounter, m_renderedFramesLastSecondCounter);

			--m_debugUpdateQueue;
		}
#endif

		if (m_oneSecondClock.GetDuration() >= Engine::Common::DateTime::SECOND_TO_NANOSECONDS)
		{
#ifdef _DEBUG
			ClearEngineCounters();
			m_debugUpdateQueue++;
#endif

			m_oneSecondClock.Reset();
		}

		m_appInstance->Update();

		++m_currentSecondUpdatesCount;
		ENGINE_FRAME_MARK_END(sl_Engine_Update);
	}

	void GameEngine::RenderFrame()
	{
		ENGINE_FRAME_MARK_START(sl_Engine_RenderFrame);



		++m_currentSecondRenderFramesCount;
		ENGINE_FRAME_MARK_END(sl_Engine_RenderFrame);
	}

	void GameEngine::ClearEngineCounters()
	{
		m_engineUpdatesLastSecondCounter = m_currentSecondUpdatesCount;
		m_renderedFramesLastSecondCounter = m_currentSecondRenderFramesCount;

		m_currentSecondUpdatesCount = 0;
		m_currentSecondRenderFramesCount = 0;
	}

	void GameEngine::EngineRun()
	{
		ClearEngineCounters();
		m_oneSecondClock.Start();

		for (;;)
		{
			if (m_timeSinceUpdateClock.GetDuration() >= m_targetUpdateFrequency || !m_timeSinceUpdateClock.IsRunning())
			{
				Update();
				m_timeSinceUpdateClock.Reset();
			}

			if (m_timeSinceRenderFrameClock.GetDuration() >= m_targetRenderFrameFrequency || !m_timeSinceRenderFrameClock.IsRunning())
			{
				m_deltaTime = m_timeSinceRenderFrameClock.GetDuration();

				RenderFrame();
				FrameMark;
				m_timeSinceRenderFrameClock.Reset();
			}
		}
	}

	void GameEngine::ShutDown()
	{
		m_appInstance->ShutDown();

#if _DEBUG
		m_debugManager.ShutDown();
#endif
	}

	GameEngine::~GameEngine()
	{
	}
}