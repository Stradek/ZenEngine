/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#ifdef _DEBUG
#include "Debug/Debug.h"
#endif // _DEBUG

#include "WindowManagement/WindowManager.h"
#include "Graphics/GraphicsManager.h"
#include "EventSystem/EventManager.h"

class IEngineApplication;

namespace Engine 
{
	class GameEngine
	{
	public:
		GameEngine(GameEngine& m_gameEngine) = delete;
		void operator=(GameEngine& m_gameEngine) = delete;

		GameEngine();

		static GameEngine& GetInstance();
		static void DestroyInstance();

		static void Run(IEngineApplication& appInstanceRef);

		Window::WindowManager& GetWindowManager() { return m_windowManager; }
		EventSystem::EventManager& GetEventManager() { return m_eventManager; }
		Graphics::GraphicsManager& GetGraphicsManager() { return m_graphicsManager; }
#ifdef _DEBUG
		Debug::DebugManager& GetDebugManager() { return m_debugManager; }
#endif

		void Close();

	private:
		static GameEngine* m_instance;

		IEngineApplication*	m_appInstance;
		
		Window::WindowManager		m_windowManager;
		EventSystem::EventManager	m_eventManager;
		Graphics::GraphicsManager	m_graphicsManager;
#ifdef _DEBUG
		Debug::DebugManager			m_debugManager;
#endif

		Common::Clock m_timeSinceUpdateClock;
		Common::Clock m_timeSinceRenderFrameClock;

		double m_deltaTime;
		bool m_shutDown;

		void SetEngineApplication(IEngineApplication& appInstanceRef);

		void StartUp();
		void ShutDown();

		void EngineRun(IEngineApplication& appInstance);

		void Update(const double deltaTime);
		void RenderFrame();
	};
}