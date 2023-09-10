/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <Engine/Core/Config.h>
#include <Engine/Core/Memory.h>

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
	using GameEngineRef = Core::Memory::ObjectPtr<GameEngine>&;

	using EngineApplicationRef = Core::Memory::ScopedObjectPtr<IEngineApplication>&;

	using WindowManagerRef = Core::Memory::ScopedObjectPtr<Window::WindowManager>&;
	using EventManagerRef = Core::Memory::ScopedObjectPtr<EventSystem::EventManager>&;
	using GraphicsManagerRef = Core::Memory::ScopedObjectPtr<Graphics::GraphicsManager>&;

#ifdef _DEBUG
	using DebugManagerRef = Core::Memory::ScopedObjectPtr<Debug::DebugManager>&;
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
		static Core::Memory::ObjectPtr<GameEngine> instance;

		Core::Memory::ScopedObjectPtr<IEngineApplication>			m_appInstance;
		
		Core::Memory::ScopedObjectPtr<Window::WindowManager>		m_windowManager;
		Core::Memory::ScopedObjectPtr<EventSystem::EventManager>	m_eventManager;
		Core::Memory::ScopedObjectPtr<Graphics::GraphicsManager>	m_graphicsManager;
#ifdef _DEBUG
		Core::Memory::ScopedObjectPtr<Debug::DebugManager>			m_debugManager;
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