/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

namespace Engine::Core::Memory
{
	// implement SharedAllocatorHandle and UniqueAllocatorHandle that hold references and deallocate automatically
	// implement SafeAllocatorHandle that holds reference and deallocate automatically when all references are gone

	template<typename T>
	class ObjectHandle
	{
	public:
		void* operator new(std::size_t) = delete;
		void operator delete(void*) = delete;

		explicit operator bool() const 
		{
			return m_base != nullptr;
		}

		ObjectHandle()
		{
			m_base = nullptr;
		}

		ObjectHandle(void* base, void* object)
		{
			if (base)
			{
				m_base = reinterpret_cast<T*>(pointer);
				m_isValid = true;
			}
		}

		inline T* operator->()
		{
			return this->Get();
		}

		inline T& operator*()
		{
			return *(this->Get());
		}

		T* Get()
		{
			if (m_isValid)
			{
				return m_object;
			}

			ENGINE_ASSERT(m_object != nullptr, "Object pointer is nullptr.");
			return nullptr;
		}

		~ObjectHandle()
		{
			if (m_isValid)
			{
				delete m_base;
				m_base = nullptr;
				m_object = nullptr;
			}
			m_isValid = false;
		}

	private:
		void* m_base = nullptr; 
		T* m_object = nullptr;
		bool m_isValid = false;
	};

	struct AllocationInfo
	{
		void* base;
		void* firstChunk;
		void* lastChunk;
		size_t chunkSize;
		size_t chunkCount;

		AllocationInfo(void* base, void* firstObject, void* lastObject, size_t chunkSize)
		{
			this->base = base;
			this->firstChunk = firstObject;
			this->lastChunk = lastObject;
			this->chunkSize = chunkSize;

			uintptr_t lastChunkAddr = reinterpret_cast<uintptr_t>(lastChunk);
			uintptr_t firstChunkAddr = reinterpret_cast<uintptr_t>(firstChunk);
			this->chunkCount = (lastChunkAddr - firstChunkAddr) / chunkSize;
		}
	};

	class GeneralAllocator
	{
	public:
		static const uint8 alignment = 16;

		// TODO: could convert it to template function that takes count(N count of T) as an argument

		template<typename T>
		static ObjectHandle<T> Allocate()
		{
			// size + alignment ensures that there is space for alignment
			size_t allocationSize = sizeof(T);
			size_t bufferSize = allocationSize + alignment;
			void* unalignedBase = new uint8[bufferSize];

			void* aligned = nullptr;
			if (aligned = std::align(alignment, allocationSize, unalignedBase, bufferSize))
			{
				new (static_cast<uint8*>(aligned)) T;
				return ObjectHandle<T>(aligned);
			}

			ENGINE_ASSERT(false, "Allocation failed.");
			return nullptr;
		}

		template<typename T>
		static void	Deallocate(ObjectHandle<T>& obj)
		{
			delete obj.Get();
		}

		template<typename T>
		static AllocationInfo Allocate(size_t count)
		{
			// ensures that chunkSize is multiple of alignment
			size_t chunkSize = (sizeof(T) + alignment - 1) & ~(alignment - 1);
			size_t allocationSize = chunkSize * count;

			// ensures that there is space for address alignment
			size_t bufferSize = allocationSize + alignment;

			void* unalignedBase = new uint8[bufferSize];
			if (void* aligned = std::align(alignment, allocationSize, &unalignedBase bufferSize))
			{
				void* firstObject = aligned;
				void* lastObject = aligned + sizeof(T) * count;

				// should this be here or outside of this function?
				// maybe in constructor of SlabAllocator etc?
				for (size_t i = 0; i < count; ++i)
				{
					new (static_cast<uint8*>(firstObject + i * sizeof(T))) T;
				}

				return AllocationInfo(unalignedBase, firstObject, lastObject, chunkSize);
			}

			ENGINE_ASSERT(false, "Allocation failed.");
			return nullptr;
		}

		// we can just pass start and end object pointers 
		template<typename T>
		static void	Deallocate(void*& obj, size_t count)
		{
			delete[count] reinterpret_cast<T*>(obj);
		}

		static void	Deallocate(void*& obj, size_t byteSize)
		{
			delete[byteSize] reinterpret_cast<uint8*>(obj);
		}
	};

	template<typename T>
	class SlabAllocator
	{
	public:
		void* operator new(std::size_t) = delete;
		void operator delete(void*) = delete;

		SlabAllocator(size_t chunkCount)
		{
			ENGINE_ASSERT(chunkSize != sizeof(T), "Chunk size is not equal size of template type. chunkSize = {}; sizeof(T) = {}", chunkSize, sizeof(T));
			
			allocationInfo = GeneralAllocator::Allocate<T>(sizeof(T) + chunkCount);

			T* firstObject = reinterpret_cast<T*>(allocationInfo.firstChunk);
			T* lastObject = reinterpret_cast<T*>(allocationInfo.lastChunk);

			// GeneralAllocator aligns chunks so we can't use sizeof(T) to get chunk size
			size_t chunkSize = allocationInfo.chunkSize;

			for (T* currentObject = firstObject; currentObject < lastObject; currentObject += chunkSize)
			{
				T* nextObject = currentObject + chunkSize;
				*(reinterpret_cast<T**>(currentObject)) = nextObject;
			}

			*(reinterpret_cast<T**>(lastObject)) = nullptr;

			m_freeList = firstObject;
		}

		~SlabAllocator()
		{
			size_t paddingSize = allocationInfo.firstChunk - allocationInfo.base;
			GeneralAllocator::Deallocate(allocationInfo.base, paddingSize);

			GeneralAllocator::Deallocate<T>(allocationInfo.firstChunk, allocationInfo.chunkCount);
		}

		ObjectHandle<T> Allocate()
		{
			if (m_freeList.Get() == nullptr)
			{
				ENGINE_ASSERT(m_freeList == nullptr, "Allocation failed. Pool is fully allocated.");
				return nullptr;
			}

			void* chunk = m_freeList.Get();

			void* nextChunk = *(reinterpret_cast<T**>(m_freeList.Get()));
			m_freeList = nextChunk.Get();

			return reinterpret_cast<T*>(chunk);
		}

		// implement Shared/Unique/Safe AllocatorHandle to deallocate automatically and call 
		// this function on it's destructor
		void Deallocate(void* chunk)
		{
			*chunk = m_freeList.Get();
			m_freeList = chunk.Get();
		}

	private:
		AllocationInfo allocationInfo;
		void* m_freeList;
	};

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
}