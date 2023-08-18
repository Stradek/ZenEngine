/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <Engine/Core/ISystem.h>

// this needs to be defined before including SDL.h 
// to avoid enforced implementation of SDL_main()
#define SDL_MAIN_HANDLED

#include <SDL.h>

namespace Engine::Graphics
{
	class GraphicsManager : Core::ISystem
	{
	public:
		void StartUp() override;
		void ShutDown() override;
	private:
		uint32 m_SDLSubsystemFlags;
		uint32 m_SDLWindowFlags;

		SDL_Window* m_SDLWindow;
	};
}