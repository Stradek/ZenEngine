/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include <GameEngine.h>

#include <Core/Core.h>

#include <stdio.h>

namespace Engine
{
	enum EngineBootingSequenceState
	{
		NotStarted,
		Initializing,
		FinishingBootingSequence,
		Finished,
	};

	Common::Time::Clock m_engineTickClock;
	Common::Time::Clock m_engineOneSecondClock;

	Common::Time::Clock m_engineUpdateClock;
	Common::Time::Clock m_renderFrameClock;

	Common::Time::Clock m_currentOperationClock;

	const uint m_targetEngineUpdatesPerSecond	= 20;
	const uint m_targetFramesPerSecond			= 60;
	const uint32 m_targetEngineUpdateTime		= static_cast<uint32>(Common::Time::SECOND_TO_NANOSECOND_RATIO / m_targetEngineUpdatesPerSecond);
	const uint32 m_targetRenderFrameTime		= static_cast<uint32>(Common::Time::SECOND_TO_NANOSECOND_RATIO / m_targetFramesPerSecond);

	uint m_engineUpdatesThisSecondCounter	= 0;
	uint m_renderedFramesThisSecondCounter	= 0;

	uint m_engineUpdatesLastSecondCounter	= 0;
	uint m_renderedFramesLastSecondCounter	= 0;

	uint32 m_lastEngineUpdateDuration	= 0;
	uint32 m_lastRenderedFrameDuration	= 0;

	double m_deltaTime = 0;

	EngineBootingSequenceState m_engineBootingState = NotStarted;

	// TODO: replace this later with event system
	uint m_debugUpdateQueue = 0;

	EngineBootingSequenceState GetBootingSequenceState()
	{
		return m_engineBootingState;
	}

	void SetBootingSequenceState(EngineBootingSequenceState bootingState)
	{
		// assert(m_engineBootingState != bootingState)

		m_engineBootingState = bootingState;
	}

	void SetNextBootingSquenceState()
	{
		EngineBootingSequenceState currentBootingSequenceState = GetBootingSequenceState();
		if (currentBootingSequenceState < EngineBootingSequenceState::Finished) // change to assert(currentBootingSequenceState < EngineBootingSequenceState::Finished)
		{
			EngineBootingSequenceState nextBootingSequenceState = static_cast<EngineBootingSequenceState>(currentBootingSequenceState + 1);
			SetBootingSequenceState(nextBootingSequenceState);
		}
	}

	void FinishBootingSequence()
	{
		m_engineTickClock.Start();
		m_engineOneSecondClock.Start();

		m_engineUpdateClock.Start();
		m_renderFrameClock.Start();

		ClearEngineCounters();
	}

	void RunBootingSequence()
	{
		SetBootingSequenceState(EngineBootingSequenceState::Initializing);

		while (GetBootingSequenceState() != EngineBootingSequenceState::Finished)
		{
			switch (GetBootingSequenceState())
			{
			case EngineBootingSequenceState::Initializing:
				InitDependencies();
				PreInit();
				Init();

				SetNextBootingSquenceState();
				break;
			case EngineBootingSequenceState::FinishingBootingSequence:
				FinishBootingSequence();

				SetBootingSequenceState(EngineBootingSequenceState::Finished);
				break;
			}
		}
	}

	void InitDependencies()
	{
		
	}

	void PreInit()
	{
		
	}

	void Init()
	{
		
	}

	void Destroy()
	{
		
	}

	void Update(double deltaTime)
	{
		m_currentOperationClock.Start();

		/* START UPDATE */

		if (m_debugUpdateQueue > 0)
		{
			double lastEngineUpdateDuration = Common::Time::UInt32ToDouble(m_lastEngineUpdateDuration);
			double lastRenderedFrameDuration = Common::Time::UInt32ToDouble(m_lastRenderedFrameDuration);

			printf("[FPS: %d] Game ms: %f; Render ms: %f; Previous CPU Tick(DeltaTime) ms: %f\n", m_renderedFramesLastSecondCounter, lastEngineUpdateDuration, lastRenderedFrameDuration, m_deltaTime);
			printf("          Game Ticks per Second: %d; Render Updates per Second: %d\n", m_engineUpdatesLastSecondCounter, m_renderedFramesLastSecondCounter);

			--m_debugUpdateQueue;
		}

		/* END UPDATE */

		m_currentOperationClock.Stop();
		m_lastEngineUpdateDuration = m_currentOperationClock.GetDuration();

		++m_engineUpdatesThisSecondCounter;
	}

	void Render()
	{
		m_currentOperationClock.Start();

		/* START RENDER */



		/* END RENDER */

		m_currentOperationClock.Stop();
		m_lastRenderedFrameDuration = m_currentOperationClock.GetDuration();

		++m_renderedFramesThisSecondCounter;
	}

	void ClearEngineCounters()
	{
		m_engineUpdatesLastSecondCounter = m_engineUpdatesThisSecondCounter;
		m_renderedFramesLastSecondCounter = m_renderedFramesThisSecondCounter;

		m_engineUpdatesThisSecondCounter = 0;
		m_renderedFramesThisSecondCounter = 0;
	}

	void Run()
	{
		// while here just to be safe and see all booting issues before starting main loop
		while (GetBootingSequenceState() != EngineBootingSequenceState::Finished)
		{
			RunBootingSequence();
		}

		while (true) // need to create good mechanism for breaking from this while when getting event or anything
		{
			m_engineTickClock.Start();

			if (m_engineUpdateClock.GetDuration() >= m_targetEngineUpdateTime)
			{
				Update(m_deltaTime);

				m_engineUpdateClock.Reset();
			}

			if (m_renderFrameClock.GetDuration() >= m_targetRenderFrameTime)
			{
				Render();
				m_renderFrameClock.Reset();
			}

			if (m_engineOneSecondClock.GetDuration() >= Engine::Common::Time::SECOND_TO_NANOSECOND_RATIO)
			{
				ClearEngineCounters();
				m_debugUpdateQueue++;

				m_engineOneSecondClock.Reset();
			}

			m_deltaTime = m_engineTickClock.GetDurationAsDouble();

			m_engineTickClock.Reset();
		}
	}
}