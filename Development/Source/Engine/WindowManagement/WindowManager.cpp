/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "WindowManager.h"

namespace Engine::Window
{
	void WindowManager::StartUp()
	{
		const uint windowWidth = 1280;
		const uint windowHeight = 720;

		m_SDLSubsystemFlags = 0 | SDL_INIT_VIDEO;
		m_SDLWindowFlags = 0;

		if (SDL_InitSubSystem(m_SDLSubsystemFlags) < 0)
		{
			ENGINE_ERROR("{}", SDL_GetError());
		}

		m_SDLWindow = SDL_CreateWindow(
			"SDLEngineTest",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			windowWidth, windowHeight,
			m_SDLWindowFlags
		);
	}

	void WindowManager::ShutDown()
	{
		SDL_DestroyWindow(m_SDLWindow);
		SDL_QuitSubSystem(m_SDLSubsystemFlags);
	}

	SDL_Window*& WindowManager::GetSDLWindowInstance()
	{
		ENGINE_FATAL_ASSERT(m_SDLWindow, "SDL Window is not initialized.");
		return m_SDLWindow;
	}
}
