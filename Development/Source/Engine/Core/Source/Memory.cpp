/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "Memory.h"

namespace Engine::Core::Memory
{
	PoolAllocator::PoolAllocator(size_t chunkSize, size_t chunkCount)
	{
		chunkSize = (chunkSize + 15) & ~15;

		m_base = Allocator::AllocateAligned<uint8>(chunkSize * chunkCount);

		for (size_t chunkIndex = 0; chunkIndex < chunkCount; ++chunkIndex)
		{
			uint8* currentChunk = m_base + chunkIndex * chunkSize;
			*(reinterpret_cast<uint8**>(currentChunk)) = currentChunk + chunkSize;
		}

		size_t lastChunkIndex = chunkCount - 1;
		*(reinterpret_cast<uint8**>(m_base + chunkSize * lastChunkIndex)) = nullptr;

		m_freeList = m_base;
	}

	void* PoolAllocator::Allocate()
	{
		if (m_freeList == nullptr)
		{
			ENGINE_ASSERT(m_freeList == nullptr, "Allocation failed. Pool is fully allocated.");
			return nullptr;
		}

		uint8* chunk = m_freeList;
		m_freeList = *(reinterpret_cast<uint8**>(m_freeList));

		return chunk;
	}

	void PoolAllocator::Deallocate(void* chunkPtr)
	{
		*(reinterpret_cast<uint8**>(chunkPtr)) = m_freeList;
		m_freeList = static_cast<uint8*>(chunkPtr);
	}

	PoolAllocator::~PoolAllocator()
	{
		Allocator::Deallocate(m_base);
	}
}