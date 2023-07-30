/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

class IEngineApplication;

namespace Engine 
{
	void RunBootingSequence();
	void FinishBootingSequence();

	void InitDependencies();
	void PreInit();
	void Init();

	void Update(double deltaTime);
	void Render();

	void ClearEngineCounters();

	void Run(IEngineApplication* gameInstance);

	void Destroy();
}