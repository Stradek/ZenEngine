/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "MemoryConfig.h"

namespace Engine::Memory
{
	class IAllocator
	{
	protected:
		size_t totalSize;

	public:
		IAllocator(const size_t totalSize) : totalSize(totalSize) {}
		virtual ~IAllocator() { totalSize = 0; }

		virtual void Init() = 0;

		virtual void* Allocate(const size_t size, const size_t alignment = MemoryConfig::DEFAULT_ALIGNMENT) = 0;
		virtual void Free(void* ptr) = 0;
	};
}