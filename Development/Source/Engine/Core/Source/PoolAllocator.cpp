/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "PoolAllocator.h"

namespace Engine::Memory
{
	void PoolAllocator::Init()
	{
		m_basePtr = malloc(totalSize);
	}

	void* PoolAllocator::Allocate(const size_t size, const size_t alignment)
	{
		return nullptr;
	}

	void PoolAllocator::Free(void* ptr)
	{

	}
}