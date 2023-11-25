/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "MemoryConfig.h"

namespace Engine::Core::Memory
{
	class GeneralAllocator
	{
	public:
		static void* Allocate(const size_t size, const size_t alignment = MemoryConfig::DEFAULT_ALIGNMENT);
		static void Free(void* ptr);
	};
}
