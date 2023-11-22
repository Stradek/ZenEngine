/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "Config.h"

namespace Engine::Core
{
	const double Config::m_targetUpdateFrequency = 1.0 / m_targetUpdatesPerSecond;
	const double Config::m_targetRenderFrameFrequency = 1.0 / m_targetLockedFramesPerSecond;
}