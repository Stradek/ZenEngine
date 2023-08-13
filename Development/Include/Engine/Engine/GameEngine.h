/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#ifdef _DEBUG

#include <Debug/Debug.h>

#endif

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

		const uint m_targetUpdatesPerSecond;
		const uint32 m_targetUpdateFrequency;
		
		const uint m_targetLockedFramesPerSecond;
		uint32 m_targetRenderFrameFrequency;

		uint32 m_deltaTime	= m_targetRenderFrameFrequency;

#ifdef _DEBUG
		Debug::DebugManager m_debugManager;
#endif

		void EngineRun();

		void StartUp();

		void Update(const uint32 deltaTime);
		void RenderFrame();

		void ShutDown();
	};
}

#ifdef _DEBUG

#define ENGINE_FRAME_MARK_START(name) {										\
	m_debugManager.GetPerformanceProfiler().FrameProfilingStart(name);	\
	FrameMarkStart(name);												\
}

#define ENGINE_FRAME_MARK_END(name) {										\
	m_debugManager.GetPerformanceProfiler().FrameProfilingEnd(name);	\
	FrameMarkEnd(name);												\
}

#else

#define ENGINE_FRAME_MARK_START(x)
#define ENGINE_FRAME_MARK_END(x)

#endif