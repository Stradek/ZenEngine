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
		GameHandle gameInstance = Engine::Core::Memory::GeneralAllocator::Allocate<Game>();
		EngineAppHandle engineAppInstance = EngineAppHandle(gameInstance.Get());
		Engine::GameEngine::Run(engineAppInstance);
	}
	return 0;
}
