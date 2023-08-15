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

		static uint32 m_targetUpdateFrequency;
		static uint32 m_targetRenderFrameFrequency;
	};
}