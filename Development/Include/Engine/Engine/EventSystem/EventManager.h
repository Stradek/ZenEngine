/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "Engine/Core/ISystem.h"

#include <SDL.h>

namespace Engine::EventSystem 
{
	class EventManager : Core::ISystem
	{
	public:
		void StartUp() override;
		void ShutDown() override;

		void Update();
	};
}