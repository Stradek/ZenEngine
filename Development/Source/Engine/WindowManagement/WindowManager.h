/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "Core/ISystem.h"

#include <SDL.h>

namespace Engine::Window
{
	class WindowManager : Core::ISystem
	{
	public:
		void StartUp() override;
		void ShutDown() override;

		SDL_Window*& GetSDLWindowInstance();
	private:
		uint32 m_SDLSubsystemFlags;
		uint32 m_SDLWindowFlags;

		SDL_Window* m_SDLWindow;
	};
}