/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

namespace Engine::Core
{
	struct Config
	{
		static constexpr size_t m_targetUpdatesPerSecond = 20;
		static constexpr size_t m_targetRenderedFramesPerSecond = 60;

		static constexpr Common::Time::Duration m_targetUpdateFrequency(Common::Time::Seconds(1).count() / m_targetRenderedFramesPerSecond);
		static constexpr Common::Time::Duration m_targetRenderingFrameFrequency(Common::Time::Seconds(1).count() / m_targetRenderedFramesPerSecond);
	};
}