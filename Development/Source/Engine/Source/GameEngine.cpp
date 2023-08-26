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
	std::shared_ptr<GameEngine> GameEngine::instance = nullptr;

	void GameEngine::Run(EngineApplicationRef appInstance)
	{
		Core::Log::Init();

		{
			GameEngineRef engineInstance = GameEngine::getInstance();

			engineInstance->SetEngineApplication(appInstance);
			engineInstance->EngineRun();
		}

		GameEngine::DestroyInstance();

		Core::Log::Close();
	}

	GameEngineRef GameEngine::getInstance()
	{
		if (instance == nullptr)
		{
			instance.reset(new GameEngine());
		}
		return instance;
	}

	void GameEngine::DestroyInstance()
	{
		ENGINE_FATAL_ASSERT(instance, "There is no engine instance.");
		ENGINE_FATAL_ASSERT(instance.use_count() == 1, "There is too much references to instance. Ref count: {}.", instance.use_count());

		instance.reset();
	}

	GameEngine::GameEngine() :
		m_deltaTime(Core::Config::m_targetRenderFrameFrequency),
		m_shutDown(false)
	{
#ifdef _DEBUG
		m_debugManager = std::make_shared<Debug::DebugManager>();
#endif

		m_windowManager = std::make_shared<Window::WindowManager>();
		m_eventManager = std::make_shared<EventSystem::EventManager>();
		m_graphicsManager = std::make_shared<Graphics::GraphicsManager>();
	}

	void GameEngine::SetEngineApplication(EngineApplicationRef appInstance)
	{
		m_appInstance = appInstance;
	}

	void GameEngine::StartUp()
	{
#ifdef _DEBUG
		m_debugManager->StartUp();
#endif

		m_windowManager->StartUp();
		m_eventManager->StartUp();
		m_graphicsManager->StartUp();

		m_appInstance->StartUp();
	}

	void GameEngine::ShutDown()
	{
		m_appInstance->ShutDown();
		m_appInstance.reset();

		m_graphicsManager->ShutDown();
		m_eventManager->ShutDown();
		m_windowManager->ShutDown();

#ifdef _DEBUG
		m_debugManager->ShutDown();
#endif

	}

	void GameEngine::Update(const uint32 deltaTime)
	{
		ENGINE_FRAME_MARK_START(sl_Engine_Update);

		m_eventManager->Update();
#ifdef _DEBUG
		m_debugManager->Update(deltaTime);
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
		m_debugManager->StartPerformanceProfiler();
#endif
		m_timeSinceUpdateClock.Start();
		m_timeSinceRenderFrameClock.Start();
		while (!m_shutDown)
		{
			if (m_timeSinceUpdateClock.GetDuration() >= Core::Config::m_targetUpdateFrequency)
			{
				Update(m_deltaTime);
#ifdef _DEBUG
				m_debugManager->AddToUpdateCounter();
#endif
				m_timeSinceUpdateClock.Reset();
			}

			if (m_timeSinceRenderFrameClock.GetDuration() >= Core::Config::m_targetRenderFrameFrequency)
			{
				m_deltaTime = m_timeSinceRenderFrameClock.GetDuration();

				RenderFrame();
#ifdef _DEBUG
				m_debugManager->AddToRenderFrameCounter();
				FrameMark;
#endif
				
				m_timeSinceRenderFrameClock.Reset();
			}
		}

		ShutDown();
	}
}