/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "Engine/GameEngine.h"

#include <Engine/IEngineApplication.h>

#include <Engine/Core/ProfilingMacros.h>

#ifdef _DEBUG
#include <Engine/Debug/Debug.h>
#endif

namespace Engine
{
	GameEngine* GameEngine::m_instance;

	void GameEngine::Run(EngineApplicationRef appInstance)
	{
		Core::Log::Init();

		{
			GameEngineRef engineInstance = GameEngine::getInstance();

			engineInstance.SetEngineApplication(appInstance);
			engineInstance.EngineRun();
		}

		GameEngine::DestroyInstance();

		Core::Log::Close();
	}

	GameEngineRef GameEngine::getInstance()
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
		// This handle should count references to it and ensure it has only one reference `instance` !!!
		// ENGINE_FATAL_ASSERT(instance.Get().use_count() == 1, "There is too much references to instance. Ref count: {}.", instance.use_count());

		delete m_instance;
	}

	GameEngine::GameEngine() :
		m_deltaTime(Core::Config::m_targetRenderFrameFrequency),
		m_shutDown(false)
	{
	}

	void GameEngine::SetEngineApplication(EngineApplicationRef appInstance)
	{
		m_appInstance = &appInstance;
	}

	void GameEngine::StartUp()
	{
#ifdef _DEBUG
		m_debugManager.StartUp();
#endif

		m_windowManager.StartUp();
		m_eventManager.StartUp();
		m_graphicsManager.StartUp();

		m_appInstance->StartUp();
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

	void GameEngine::Update(const uint32 deltaTime)
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

	void GameEngine::EngineRun()
	{
		StartUp();

#ifdef _DEBUG
		m_debugManager.StartDebugManagerClock();
#endif
		m_timeSinceUpdateClock.Start();
		m_timeSinceRenderFrameClock.Start();
		while (!m_shutDown)
		{
			if (m_timeSinceUpdateClock.GetDuration() >= Core::Config::m_targetUpdateFrequency)
			{
				Update(m_deltaTime);

				m_timeSinceUpdateClock.Reset();
			}

			if (m_timeSinceRenderFrameClock.GetDuration() >= Core::Config::m_targetRenderFrameFrequency)
			{
				m_deltaTime = m_timeSinceRenderFrameClock.GetDuration();

				RenderFrame();
				ENGINE_FRAME_MARK();
				
				m_timeSinceRenderFrameClock.Reset();
			}
		}

		ShutDown();
	}
}