/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

namespace Engine::Core::Memory
{
	template<typename T, const size_t size>
	class CircularBuffer
	{
	public:
		
		CircularBuffer() : m_bufferSize(size), m_currentIndex(0)
		{
		}

		void EmplaceBack(const T item)
		{
			m_buffer[m_currentIndex] = item;
			m_currentIndex = ++m_currentIndex % size;
		}

		std::vector<T> GetAll()
		{
			std::vector<T> bufferItems;
			for (size_t i = 0; i < m_bufferSize; ++i)
			{
				bufferItems.push_back(m_buffer[i]);
			}

			return bufferItems;
		}

		uint GetCurrentIndex()
		{
			return m_currentIndex;
		}

	private:
		size_t m_bufferSize;
		T m_buffer[size];
		uint m_currentIndex;
	};

	class Allocator
	{
	public:
		template <typename T>
		static T* AllocateAligned(size_t size)
		{
			ENGINE_FATAL_ASSERT(alignof(T) > alignment, 
								"Failed to allocate object T of size: {}, \
								larger than alignment requirements of size {}.", 
								sizeof(T), alignment);

			void* unalignedBase = new uint8[size];
			if (std::align(alignment, sizeof(T), unalignedBase, size))
			{
				T* alignedBase = reinterpret_cast<T*>(unalignedBase);
				return alignedBase;
			}

			ENGINE_ASSERT(false, "Allocation failed.");
			return nullptr;
		}

		static void	Deallocate(void* obj)
		{
			delete[] obj;
			obj = nullptr;
		}

		static const uint8 alignment = 16;
	};

	class PoolAllocator
	{
	public:
		PoolAllocator(size_t chunkSize, size_t chunkCount);
		~PoolAllocator();
		void* Allocate();
		void Deallocate(void* chunkPtr);
	private:
		uint8* m_base;
		uint8* m_freeList;
	};
}