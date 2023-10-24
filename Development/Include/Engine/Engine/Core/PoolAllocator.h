/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "IAllocator.h"

namespace Engine::Memory
{
	class PoolAllocator : public IAllocator
	{
	private:
		const size_t m_chunkSize = 16;
		void* m_basePtr = nullptr;

	public:
		PoolAllocator(const size_t totalSize) : IAllocator(totalSize) {};

		void Init() override;

		void* Allocate(const size_t size, const size_t alignment = 0) override;
		void Free(void* ptr) override;
	};
}