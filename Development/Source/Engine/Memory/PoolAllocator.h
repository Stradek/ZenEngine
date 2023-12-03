/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "IAllocator.h"

namespace Engine::Core::Memory
{
	template <typename Type>
	class PoolAllocator : public IAllocator<Type>
	{
	private:
		const size_t m_chunkSize = 16;
		void* m_basePtr = nullptr;

	public:
		PoolAllocator(const size_t totalSize) : IAllocator(totalSize) {};
	};
}