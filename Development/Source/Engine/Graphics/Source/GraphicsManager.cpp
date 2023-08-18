/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "GraphicsManager.h"

namespace Engine::Graphics
{
	void GraphicsManager::StartUp()
	{
		m_SDLSubsystemFlags = 0 | SDL_INIT_VIDEO;
		m_SDLWindowFlags	= 0;

		if (SDL_InitSubSystem(m_SDLSubsystemFlags) < 0)
		{
			ENGINE_ERROR("{}", SDL_GetError());
		}

		const uint windowWidth = 1280;
		const uint windowHeight = 720;

		m_SDLWindow = SDL_CreateWindow(
			"SDLEngineTest",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			windowWidth, windowHeight,
			m_SDLWindowFlags
		);
	}

	void GraphicsManager::ShutDown()
	{
		SDL_DestroyWindow(m_SDLWindow);
		SDL_QuitSubSystem(m_SDLSubsystemFlags);
	}
}
