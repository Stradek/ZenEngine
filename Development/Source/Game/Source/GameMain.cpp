/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include <Game.h>

#include <Engine/GameEngine.h>
#include <Engine/Core/Memory.h>

using GameHandle = Engine::Core::Memory::ObjectHandle<Game>;
using EngineAppHandle = Engine::Core::Memory::ObjectHandle<IEngineApplication>;

int main(int argc, char* argv[])
{
	{
		Engine::Core::Memory::ScopedObjectPtr<IEngineApplication> gameInstance = Engine::Core::Memory::GeneralAllocator::Allocate<Game>();
		Engine::GameEngine::Run(gameInstance);
	}

	return 0;
}
