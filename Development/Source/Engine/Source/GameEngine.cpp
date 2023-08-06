/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "GameEngine.h"

#include <IEngineApplication.h>
#include <Debug/Debug.h>

#include <tracy/Tracy.hpp>

namespace Engine
{
	void GameEngine::Run(std::unique_ptr<IEngineApplication> appInstance)
	{
		GameEngine engineInstance = GameEngine(std::move(appInstance));
		engineInstance.EngineRun();
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

		ENGINE_FATAL_ASSERT(currentBootingSequenceState < EngineBootingSequenceState::Finished, "Can't set next booting state as there is none after Finished state.");
			
		EngineBootingSequenceState nextBootingSequenceState = static_cast<EngineBootingSequenceState>(currentBootingSequenceState + 1);
		SetBootingSequenceState(nextBootingSequenceState);
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

	void GameEngine::FinishBootingSequence()
	{
		ClearEngineCounters();
		m_oneSecondClock.Start();
	}

	void GameEngine::ClearEngineCounters()
	{
		m_engineUpdatesLastSecondCounter = m_currentSecondUpdatesCount;
		m_renderedFramesLastSecondCounter = m_currentSecondRenderFramesCount;

		m_currentSecondUpdatesCount = 0;
		m_currentSecondRenderFramesCount = 0;
	}

	void GameEngine::Update()
	{
		FrameMarkStart(sl_Engine_Update);

		if (m_oneSecondClock.GetDuration() >= Engine::Common::DateTime::SECOND_TO_NANOSECONDS)
		{
			ClearEngineCounters();
			m_debugUpdateQueue++;

			m_oneSecondClock.Reset();
		}

		if (m_debugUpdateQueue > 0)
		{
			double deltaTime = m_deltaTime * Common::DateTime::NANOSECOND_TO_MILISECONDS;

			ENGINE_LOG("[FPS: {}] Game Update ms: [WIP]; Render ms: [WIP]; Previous Render Update (DeltaTime) ms: {:.4f}", m_renderedFramesLastSecondCounter, deltaTime);
			ENGINE_LOG("          Game Updates per Second: {}; Render Updates per Second: {}", m_engineUpdatesLastSecondCounter, m_renderedFramesLastSecondCounter);

			--m_debugUpdateQueue;
		}

		m_appInstance->Update();

		++m_currentSecondUpdatesCount;
		FrameMarkEnd(sl_Engine_Update);
	}

	void GameEngine::RenderFrame()
	{
		FrameMarkStart(sl_Engine_RenderFrame);



		++m_currentSecondRenderFramesCount;
		FrameMarkEnd(sl_Engine_RenderFrame);
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
			if (m_timeSinceUpdateClock.GetDuration() >= m_targetUpdateFrequency || !m_timeSinceUpdateClock.IsRunning())
			{
				Update();
				m_timeSinceUpdateClock.Reset();
			}

			if (m_timeSinceRenderFrameClock.GetDuration() >= m_targetRenderFrameFrequency || !m_timeSinceRenderFrameClock.IsRunning())
			{
				m_deltaTime = m_timeSinceRenderFrameClock.GetDuration();

				RenderFrame();
				FrameMark;
				m_timeSinceRenderFrameClock.Reset();
			}


		}
	}

	GameEngine::~GameEngine()
	{
		m_appInstance->Close();
	}
}