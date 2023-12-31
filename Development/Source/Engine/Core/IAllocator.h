/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "MemoryConfig.h"

namespace Engine::Core::Memory
{
	template <typename Type>
	class IAllocator
	{
	protected:
		size_t totalSize;

	public:
		IAllocator(const size_t totalSize) : totalSize(totalSize) {}
		virtual ~IAllocator() { totalSize = 0; }

		virtual void Init() = 0;

		virtual void* Allocate(const size_t size);

		virtual void Free(void* ptr) = 0;
		virtual void Reset();
	};
}