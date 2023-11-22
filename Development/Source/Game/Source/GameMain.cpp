/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "Game.h"
#include "Engine/GameEngine.h"

int main(int argc, char* argv[])
{
	{
		IEngineApplication* gameInstance = new Game();
		Engine::GameEngine::Run(*gameInstance);
	}

	return 0;
}
