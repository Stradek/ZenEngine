/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "Engine/Core/ISystem.h"

namespace Engine::Graphics
{
	class GraphicsManager : Core::ISystem
	{
	public:
		void StartUp() override;
		void ShutDown() override;
	};
}