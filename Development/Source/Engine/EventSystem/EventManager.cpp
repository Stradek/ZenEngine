/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "EventManager.h"

#include "GameEngine.h"
#include "WindowManagement/WindowManager.h"

#include <SDL.h>

void Engine::EventSystem::EventManager::StartUp()
{

}

void Engine::EventSystem::EventManager::ShutDown()
{
	
}

void Engine::EventSystem::EventManager::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {  
		if (event.type == SDL_WINDOWEVENT)
		{
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_CLOSE:
				GameEngine::GetInstance().Close();
				break;
			}
		}
	}
}
