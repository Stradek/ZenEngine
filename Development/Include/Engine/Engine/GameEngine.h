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
		GameEngine(std::unique_ptr<IEngineApplication>  appInstance);

		enum EngineBootingSequenceState
		{
			NotStarted,
			Initializing,
			Finalizing,
			Finished,
		};

		std::unique_ptr<IEngineApplication> m_appInstance;

		Common::DateTime::Clock m_engineMainLoopClock;
		Common::DateTime::Clock m_engineUpdateClock;
		Common::DateTime::Clock m_engineRenderFrameClock;

		Common::DateTime::Clock m_currentOperationClock;
		Common::DateTime::Clock m_engineOneSecondClock;

		EngineBootingSequenceState m_engineBootingState = NotStarted;

		static constexpr uint m_targetEngineUpdatesPerSecond	= 20;
		static constexpr uint m_targetFramesPerSecond			= 60;
		static constexpr uint32 m_targetEngineUpdateTime		= static_cast<uint32>(Common::DateTime::SECOND_TO_NANOSECONDS / m_targetEngineUpdatesPerSecond);
		static constexpr uint32 m_targetRenderFrameTime			= static_cast<uint32>(Common::DateTime::SECOND_TO_NANOSECONDS / m_targetFramesPerSecond);

		uint32 m_deltaTime	= m_targetRenderFrameTime;

		uint m_engineUpdatesThisSecondCounter	= 0;
		uint m_engineUpdatesLastSecondCounter	= 0;
		uint32 m_lastEngineUpdateDuration		= 0;

		uint m_renderedFramesThisSecondCounter	= 0;
		uint m_renderedFramesLastSecondCounter	= 0;
		uint32 m_lastRenderedFrameDuration		= 0;

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
		void Render();

		void ClearEngineCounters();

		void Close();
	};
}