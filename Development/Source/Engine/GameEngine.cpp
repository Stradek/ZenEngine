/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "GameEngine.h"

#include "IEngineApplication.h"
#include "Core/Config.h"
#include "Core/ProfilingMacros.h"

#ifdef _DEBUG
#include "Debug/Debug.h"
#endif

namespace Engine
{
	GameEngine* GameEngine::m_instance;

	void GameEngine::Run(IEngineApplication& appInstance)
	{
		Core::Log::Init();

		{
			GameEngine& engineInstance = GameEngine::GetInstance();
			engineInstance.EngineRun(appInstance);
		}

		GameEngine::DestroyInstance();
		Core::Log::Close();
	}

	GameEngine& GameEngine::GetInstance()
	{
		if (!m_instance)
		{
			m_instance = new GameEngine();
			ENGINE_ASSERT(m_instance, "Failed to allocate engine instance.");
		}
		return *m_instance;
	}

	void GameEngine::DestroyInstance()
	{
		ENGINE_FATAL_ASSERT(m_instance, "There is no engine instance.");
		
		delete m_instance;
	}

	GameEngine::GameEngine() :
		m_appInstance(nullptr),
		m_deltaTime(Core::Config::m_targetRenderFrameFrequency),
		m_shutDown(false)
	{
	}

	void GameEngine::SetEngineApplication(IEngineApplication& appInstance)
	{
		m_appInstance = &appInstance;
	}

	void GameEngine::StartUp()
	{
		// StartUp engine systems
#ifdef _DEBUG
		m_debugManager.StartUp();
#endif

		m_windowManager.StartUp();
		m_eventManager.StartUp();
		m_graphicsManager.StartUp();

		m_appInstance->StartUp();

		// StartUp engine clocks
#ifdef _DEBUG
		m_debugManager.StartDebugManagerClock();
#endif
		m_timeSinceUpdateClock.Start();
		m_timeSinceRenderFrameClock.Start();
	}

	void GameEngine::ShutDown()
	{
		m_appInstance->ShutDown();
		m_graphicsManager.ShutDown();
		m_eventManager.ShutDown();
		m_windowManager.ShutDown();

#ifdef _DEBUG
		m_debugManager.ShutDown();
#endif
	}

	void GameEngine::Update(const double deltaTime)
	{
		ENGINE_FRAME_MARK_START(sl_Engine_Update);

		m_eventManager.Update();
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

	void GameEngine::Close()
	{
		m_shutDown = true;
	}

	void GameEngine::EngineRun(IEngineApplication& appInstance)
	{
		SetEngineApplication(appInstance);

		StartUp();

		while (!m_shutDown)
		{
			if (m_timeSinceUpdateClock.GetDuration().GetSeconds() >= Core::Config::m_targetUpdateFrequency)
			{
 				Update(m_deltaTime);

				m_timeSinceUpdateClock.Reset();
			}

			if (m_timeSinceRenderFrameClock.GetDuration().GetSeconds() >= Core::Config::m_targetRenderFrameFrequency)
			{
				m_deltaTime = m_timeSinceRenderFrameClock.GetDuration().GetSeconds();

				RenderFrame();
				ENGINE_FRAME_MARK();
				
				m_timeSinceRenderFrameClock.Reset();
			}
		}

		ShutDown();
	}
}