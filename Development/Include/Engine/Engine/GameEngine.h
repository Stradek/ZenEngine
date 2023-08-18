/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <Engine/Core/Config.h>

#ifdef _DEBUG
#include <Engine/Debug/Debug.h>
#endif // _DEBUG
#include <Engine/Graphics/GraphicsManager.h>

class ISystem;
class IEngineApplication;

namespace Engine 
{
	class GameEngine
	{
	public:
		static void Run(std::unique_ptr<IEngineApplication> appInstance);

	private:
		GameEngine(std::unique_ptr<IEngineApplication> appInstance);
		~GameEngine();

		std::unique_ptr<IEngineApplication> m_appInstance;

		Common::DateTime::Clock m_timeSinceUpdateClock;
		Common::DateTime::Clock m_timeSinceRenderFrameClock;
		
#ifdef _DEBUG
		Debug::DebugManager m_debugManager;
#endif
		Graphics::GraphicsManager m_renderingSystem;

		uint32 m_deltaTime	= Core::Config::m_targetRenderFrameFrequency;

		void EngineRun();

		void StartUp();

		void Update(const uint32 deltaTime);
		void RenderFrame();

		void ShutDown();
	};
}