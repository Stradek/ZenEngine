/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "GameEngine.h"

#include <IEngineApplication.h>
#include <Core/Log.h>

namespace Engine
{

	void GameEngine::Run(std::unique_ptr<IEngineApplication> appInstance)
	{
		GameEngine gameEngineInstance = GameEngine(std::move(appInstance));
		gameEngineInstance.EngineRun();
	}

	GameEngine::GameEngine(std::unique_ptr<IEngineApplication> appInstance) :
		m_appInstance(std::move(appInstance))
	{
		
	}

	GameEngine::EngineBootingSequenceState GameEngine::GetBootingSequenceState()
	{
		return m_engineBootingState;
	}

	void GameEngine::SetBootingSequenceState(EngineBootingSequenceState bootingState)
	{
		ENGINE_ASSERT(m_engineBootingState != bootingState, "Engine booting state is already set to the same value.");

		m_engineBootingState = bootingState;
	}

	void GameEngine::SetNextBootingSquenceState()
	{
		EngineBootingSequenceState currentBootingSequenceState = GetBootingSequenceState();

		ENGINE_FATAL_ASSERT(currentBootingSequenceState < EngineBootingSequenceState::Finished, "Can't set next booting state as there is none after Finished.");
			
		EngineBootingSequenceState nextBootingSequenceState = static_cast<EngineBootingSequenceState>(currentBootingSequenceState + 1);
		SetBootingSequenceState(nextBootingSequenceState);
	}

	void GameEngine::FinishBootingSequence()
	{
		m_engineMainLoopClock.Start();
		m_engineOneSecondClock.Start();

		m_engineUpdateClock.Start();
		m_engineRenderFrameClock.Start();

		ClearEngineCounters();
	}

	void GameEngine::RunBootingSequence()
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
			case EngineBootingSequenceState::Finalizing:
				FinishBootingSequence();

				SetBootingSequenceState(EngineBootingSequenceState::Finished);
				break;
			}
		}
	}

	void GameEngine::InitDependencies()
	{
		
	}

	void GameEngine::PreInit()
	{
		
	}

	void GameEngine::Init()
	{
		m_appInstance->Init();
	}

	void GameEngine::Update()
	{
		m_currentOperationClock.Start();

		/* START UPDATE */


		if (m_debugUpdateQueue > 0)
		{
			double lastEngineUpdateDuration		= m_lastEngineUpdateDuration	* Common::DateTime::NANOSECOND_TO_MILISECONDS;
			double lastRenderedFrameDuration	= m_lastRenderedFrameDuration	* Common::DateTime::NANOSECOND_TO_MILISECONDS;
			double deltaTime					= m_deltaTime					* Common::DateTime::NANOSECOND_TO_MILISECONDS;

			ENGINE_LOG("[FPS: {}] Game Update ms: {:.4f}; Render ms: {:.4f}; Previous Render Update (DeltaTime) ms: {:.4f}", m_renderedFramesLastSecondCounter, lastEngineUpdateDuration, lastRenderedFrameDuration, deltaTime);
			ENGINE_LOG("          Game Updates per Second: {}; Render Updates per Second: {}", m_engineUpdatesLastSecondCounter, m_renderedFramesLastSecondCounter);

			--m_debugUpdateQueue;
		}

		m_appInstance->Update();

		/* END UPDATE */

		m_currentOperationClock.Stop();
		m_lastEngineUpdateDuration = m_currentOperationClock.GetDuration();

		++m_engineUpdatesThisSecondCounter;
	}

	void GameEngine::Render()
	{
		m_currentOperationClock.Start();

		/* START RENDER */



		/* END RENDER */

		m_currentOperationClock.Stop();
		m_lastRenderedFrameDuration = m_currentOperationClock.GetDuration();

		++m_renderedFramesThisSecondCounter;
	}

	void GameEngine::ClearEngineCounters()
	{
		m_engineUpdatesLastSecondCounter = m_engineUpdatesThisSecondCounter;
		m_renderedFramesLastSecondCounter = m_renderedFramesThisSecondCounter;

		m_engineUpdatesThisSecondCounter = 0;
		m_renderedFramesThisSecondCounter = 0;
	}

	void GameEngine::EngineRun()
	{
		Core::Log::Init();

		// while here just to be safe and see all booting issues before starting main loop
		while (GetBootingSequenceState() != EngineBootingSequenceState::Finished)
		{
			RunBootingSequence();
		}

		while (true) // need to implement good mechanism for breaking from this while when getting event or anything
		{
			m_engineMainLoopClock.Start();

			if (m_engineUpdateClock.GetDuration() >= m_targetEngineUpdateTime)
			{
				Update();

				m_engineUpdateClock.Reset();
			}

			if (m_engineRenderFrameClock.GetDuration() >= m_targetRenderFrameTime)
			{
				Render();
				m_engineRenderFrameClock.Reset();

				m_deltaTime = m_engineMainLoopClock.GetDuration();
			}

			if (m_engineOneSecondClock.GetDuration() >= Engine::Common::DateTime::SECOND_TO_NANOSECONDS)
			{
				ClearEngineCounters();
				m_debugUpdateQueue++;

				m_engineOneSecondClock.Reset();
			}

			m_engineMainLoopClock.Reset();
		}
	}

	GameEngine::~GameEngine()
	{
		m_appInstance->Close();
	}
}