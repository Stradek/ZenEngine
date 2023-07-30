/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include <Game.h>

#include <Engine/GameEngine.h>

int main(int argc, char* argv[])
{
	Game gameInstance = Game();
	Engine::Run(&gameInstance);
}