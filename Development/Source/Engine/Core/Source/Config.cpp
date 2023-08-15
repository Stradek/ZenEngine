/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "Config.h"

namespace Engine::Core
{
	uint32 Config::m_targetUpdateFrequency = static_cast<uint32>(Common::DateTime::SECOND_TO_NANOSECONDS / m_targetUpdatesPerSecond);
	uint32 Config::m_targetRenderFrameFrequency = static_cast<uint32>(Common::DateTime::SECOND_TO_NANOSECONDS / m_targetLockedFramesPerSecond);
}
