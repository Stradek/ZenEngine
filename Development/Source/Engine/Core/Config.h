/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

namespace Engine::Core
{
	class Config
	{
	public:
		static constexpr size_t Config::m_targetUpdatesPerSecond = 20;
		static constexpr size_t Config::m_targetLockedFramesPerSecond = 60;

		static constexpr std::chrono::high_resolution_clock::duration Config::m_targetUpdateFrequency = std::chrono::high_resolution_clock::duration(1 * Common::SECOND_TO_NANOSECONDS / m_targetUpdatesPerSecond);
		static constexpr std::chrono::high_resolution_clock::duration Config::m_targetRenderFrameFrequency = std::chrono::high_resolution_clock::duration(1 * Common::SECOND_TO_NANOSECONDS / m_targetLockedFramesPerSecond);
	};
}