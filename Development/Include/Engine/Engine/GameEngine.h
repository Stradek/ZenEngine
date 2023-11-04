/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <Engine/Core/Config.h>

#ifdef _DEBUG
#include <Engine/Debug/Debug.h>
#endif // _DEBUG

#include <Engine/WindowManagement/WindowManager.h>
#include <Engine/Graphics/GraphicsManager.h>
#include <Engine/EventSystem/EventManager.h>


class ISystem;
class IEngineApplication;

namespace Engine 
{
	class GameEngine;
	using GameEngineRef = GameEngine&;

	using EngineApplicationRef = IEngineApplication&;

	using WindowManagerRef = Window::WindowManager&;
	using EventManagerRef = EventSystem::EventManager&;
	using GraphicsManagerRef = Graphics::GraphicsManager&;

#ifdef _DEBUG
	using DebugManagerRef = Debug::DebugManager&;
#endif

	class GameEngine
	{
	public:
		GameEngine(GameEngine& m_gameEngine) = delete;
		void operator=(GameEngine& m_gameEngine) = delete;

		GameEngine();

		static GameEngineRef getInstance();
		static void DestroyInstance();

		static void Run(EngineApplicationRef appInstanceRef);

		WindowManagerRef GetWindowManager() { return m_windowManager; }
		EventManagerRef GetEventManager() { return m_eventManager; }
		GraphicsManagerRef GetGraphicsManager() { return m_graphicsManager; }
#ifdef _DEBUG
		DebugManagerRef GetDebugManager() { return m_debugManager; }
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

		void SetEngineApplication(EngineApplicationRef appInstanceRef);

		void StartUp();
		void ShutDown();

		void EngineRun();

		void Update(const double deltaTime);
		void RenderFrame();
	};
}