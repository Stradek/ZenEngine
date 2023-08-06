/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

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

		enum EngineBootingSequenceState
		{
			NotStarted,
			Initializing,
			Finalizing,
			Finished,
		};

		std::unique_ptr<IEngineApplication> m_appInstance;

		Common::DateTime::Clock m_timeSinceUpdateClock;
		Common::DateTime::Clock m_timeSinceRenderFrameClock;
		Common::DateTime::Clock m_oneSecondClock;

		EngineBootingSequenceState m_engineBootingState = NotStarted;

		const uint m_targetUpdatesPerSecond			= 20;
		const uint m_targetFramesPerSecond			= 60;
		const uint32 m_targetUpdateFrequency		= static_cast<uint32>(Common::DateTime::SECOND_TO_NANOSECONDS / m_targetUpdatesPerSecond);
		const uint32 m_targetRenderFrameFrequency	= static_cast<uint32>(Common::DateTime::SECOND_TO_NANOSECONDS / m_targetFramesPerSecond);

		uint32 m_deltaTime	= m_targetRenderFrameFrequency;

		uint m_currentSecondUpdatesCount		= 0;
		uint m_engineUpdatesLastSecondCounter	= 0;

		uint m_currentSecondRenderFramesCount	= 0;
		uint m_renderedFramesLastSecondCounter	= 0;

		uint m_debugUpdateQueue = 0;

		void EngineRun();

		EngineBootingSequenceState GetBootingSequenceState();
		void SetBootingSequenceState(EngineBootingSequenceState bootingState);
		void SetNextBootingSquenceState();
		void FinishBootingSequence();

		void RunBootingSequence();

		void InitDependencies();
		void PreInit();
		void Init();

		void Update();
		void RenderFrame();

		void ClearEngineCounters();
	};
}