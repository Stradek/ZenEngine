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
		static constexpr uint m_targetUpdatesPerSecond = 20;
		static constexpr uint m_targetLockedFramesPerSecond = 60;

		static constexpr uint32 m_targetUpdateFrequency = static_cast<uint32>(Common::DateTime::SECOND_TO_NANOSECONDS / m_targetUpdatesPerSecond);
		static constexpr uint32 m_targetRenderFrameFrequency = static_cast<uint32>(Common::DateTime::SECOND_TO_NANOSECONDS / m_targetLockedFramesPerSecond);
	};
}