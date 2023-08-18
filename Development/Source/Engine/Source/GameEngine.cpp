/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "Engine/GameEngine.h"

#include <Engine/IEngineApplication.h>

#include <Engine/Debug/DebugMacros.h>

#ifdef _DEBUG
#include <Engine/Debug/Debug.h>
#endif

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
		m_renderingSystem.StartUp();

		m_appInstance->StartUp();
	}

	void GameEngine::Update(const uint32 deltaTime)
	{
		ENGINE_FRAME_MARK_START(sl_Engine_Update);

#ifdef _DEBUG
		m_debugManager.Update(deltaTime);
#endif

		m_appInstance->Update(deltaTime);

		ENGINE_FRAME_MARK_END(sl_Engine_Update);
	}

	void GameEngine::RenderFrame()
	{
		ENGINE_FRAME_MARK_START(sl_Engine_RenderFrame);

		ENGINE_FRAME_MARK_END(sl_Engine_RenderFrame);
	}

	void GameEngine::EngineRun()
	{
		m_timeSinceUpdateClock.Start();
		m_timeSinceRenderFrameClock.Start();

#ifdef _DEBUG
		m_debugManager.StartPerformanceProfiler();
#endif
		for (;;)
		{
			if (m_timeSinceUpdateClock.GetDuration() >= Core::Config::m_targetUpdateFrequency)
			{
				Update(m_deltaTime);
#ifdef _DEBUG
				m_debugManager.AddToUpdateCounter();
#endif
				m_timeSinceUpdateClock.Reset();
			}

			if (m_timeSinceRenderFrameClock.GetDuration() >= Core::Config::m_targetRenderFrameFrequency)
			{
				m_deltaTime = m_timeSinceRenderFrameClock.GetDuration();

				RenderFrame();
#ifdef _DEBUG
				m_debugManager.AddToRenderFrameCounter();
				FrameMark;
#endif
				
				m_timeSinceRenderFrameClock.Reset();
			}
		}
	}

	void GameEngine::ShutDown()
	{
		m_appInstance->ShutDown();

		m_renderingSystem.ShutDown();
#ifdef _DEBUG
		m_debugManager.ShutDown();
#endif
	}

	GameEngine::~GameEngine()
	{
	}
}