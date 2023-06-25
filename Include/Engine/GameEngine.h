#pragma once

#include <Common/Clock.h>
#include <Core/ISystem.h>

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

	void Run();

	void Destroy();
}