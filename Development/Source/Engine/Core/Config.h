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

		static constexpr double Config::m_targetUpdateFrequency = 1.0 / m_targetUpdatesPerSecond;
		static constexpr double Config::m_targetRenderFrameFrequency = 1.0 / m_targetLockedFramesPerSecond;
	};
}