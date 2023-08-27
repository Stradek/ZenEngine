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
	using GameEngineRef = std::shared_ptr<GameEngine>&;

	using EngineApplicationPtr = std::shared_ptr<IEngineApplication>;
	using EngineApplicationRef = EngineApplicationPtr&;

	using WindowManagerRef = std::shared_ptr<Window::WindowManager>&;
	using EventManagerRef = std::shared_ptr<EventSystem::EventManager>&;
	using GraphicsManagerRef = std::shared_ptr<Graphics::GraphicsManager>&;

#ifdef _DEBUG
	using DebugManagerRef = std::shared_ptr<Debug::DebugManager>&;
#endif

	class GameEngine
	{
	public:
		GameEngine(GameEngine& m_gameEngine) = delete;
		void operator=(GameEngine& m_gameEngine) = delete;

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
		GameEngine();

		static std::shared_ptr<GameEngine> instance;

		std::shared_ptr<IEngineApplication> m_appInstance;
		
		std::shared_ptr<Window::WindowManager>		m_windowManager;
		std::shared_ptr<EventSystem::EventManager>	m_eventManager;
		std::shared_ptr<Graphics::GraphicsManager>	m_graphicsManager;
#ifdef _DEBUG
		std::shared_ptr<Debug::DebugManager>		m_debugManager;
#endif

		Common::DateTime::Clock m_timeSinceUpdateClock;
		Common::DateTime::Clock m_timeSinceRenderFrameClock;

		uint32 m_deltaTime;
		bool m_shutDown;

		void SetEngineApplication(EngineApplicationRef appInstanceRef);

		void StartUp();
		void ShutDown();

		void EngineRun();

		void Update(const uint32 deltaTime);
		void RenderFrame();
	};
}