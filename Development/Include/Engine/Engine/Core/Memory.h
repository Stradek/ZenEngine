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
	struct ObjectAllocationInfo
	{
		void* base;
		size_t allocationSize;
		
		T* object;
		size_t objectSize;
	};

	struct AllocationInfo
	{
		// TODO: 
		// - we should add here bool for allocation validation
		// - refactor that
		// - decouple implementation to class, leave here data only
		void* base;
		void* firstChunk;
		void* lastChunk;
		size_t chunkSize;
		size_t chunkCount;

		AllocationInfo(void* base, void* firstObject, void* lastObject, size_t chunkSize) :
			base(base), firstChunk(firstObject), lastChunk(lastObject), chunkSize(chunkSize)
		{
			uintptr_t lastChunkAddr = reinterpret_cast<uintptr_t>(lastChunk);
			uintptr_t firstChunkAddr = reinterpret_cast<uintptr_t>(firstChunk);

			this->chunkCount = (lastChunkAddr - firstChunkAddr) / chunkSize;
		}
	};

	template<typename T>
	class ObjectPtr
	{
	public:
		ObjectPtr() : m_allocationInfo() {}
		ObjectPtr(ObjectAllocationInfo<T>& allocationInfo) : m_allocationInfo(allocationInfo) {}

		template<typename U>
		ObjectPtr(ObjectAllocationInfo<U>& allocationInfo) : m_allocationInfo(allocationInfo) {}

		T* Get()
		{
			if (!m_isValid)
			{
				return nullptr;
			}

			return m_allocationInfo.object;
		}

		bool IsValid()
		{
			return m_isValid;
		}

		explicit operator bool() const
		{
			return IsValid();
		}

		inline T* operator->()
		{
			return this->Get();
		}

		inline T& operator*()
		{
			return *(this->Get());
		}
	private:
		ObjectAllocationInfo<T> m_allocationInfo;
	};

	template<typename T>
	class ScopedObjectPtr : public ObjectPtr<T>
	{
	public:
		ScopedObjectPtr() : ObjectPtr<T>() {}

		ScopedObjectPtr<T>& operator=(const ObjectPtr<T>& objectPtr)
		{
			ENGINE_ASSERT(objectPtr, "Object is not valid.");
			ENGINE_ASSERT(this != &objectPtr, "Objects are the same.");

			Release();
			ScopedObjectPtr<T>(objectPtr);

			return *this;
		}
		//template<typename U>
		//ScopedObjectPtr(const ObjectPtr<U>& objectPtr) : ObjectPtr<T>(objectPtr) {}

		//ScopedObjectPtr(const ObjectPtr<T>& objectPtr) : ObjectPtr<T>(objectPtr) {}

		void Release()
		{
			if (IsValid())
			{
				FreeAllocator();
			}
		}

		~ScopedObjectPtr()
		{
			Release();
		}

		ScopedObjectPtr(const ScopedObjectPtr<T>& other) = delete;
	protected:
		bool m_isValid = false;

		void FreeAllocator()
		{
			delete[m_allocationInfo.allocationSize] m_allocationInfo.base;
		}
	};

	template<typename T>
	class ObjectHandle
	{
	public:
		explicit operator bool() const 
		{
			return m_isValid;
		}

		ObjectHandle() : m_isValid(false), m_objectPtr()
#ifdef _DEBUG
			,m_object(nullptr)
#endif
		{

		}

		ObjectHandle(const ObjectPtr<T>& objectPtr) :
			m_isValid(false), 
			m_objectPtr(objectPtr)
#ifdef _DEBUG
			, m_object(objectPtr.Get())
#endif
		{
			auto& allocationInfo = m_objectPtr.GetAllocationInfo();
			if (allocationInfo.base == nullptr || allocationInfo.object == nullptr ||
				allocationInfo.allocationSize <= 0 || allocationInfo.objectSize <= 0)
			{
				m_isValid = false;
				return;
			}
			else
			{
				m_isValid = true;
			}
		}

		template<typename U>
		ObjectHandle(const ObjectHandle<U>& otherObjectHandle) : ObjectHandle(other->GetAllocationInfo()) {}

		ObjectHandle(const ObjectHandle<T>& other) : ObjectHandle(other->GetAllocationInfo()) {}
		
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
				return m_allocationInfo.object;
			}

			ENGINE_ASSERT(m_isValid, "Object handle is not valid.");
			return nullptr;
		}

		ObjectAllocationInfo<T> GetAllocationInfo()
		{
			if (m_isValid)
			{
				return m_allocationInfo;
			}

			return ObjectAllocationInfo<T>();
		}

		void Invalidate()
		{
			m_isValid = false;
		}

		~ObjectHandle()
		{
			Release();
		}

		void* operator new(std::size_t) = delete;
		void operator delete(void*) = delete;

	protected:
		bool m_isValid;

		const ObjectPtr<T> m_objectPtr;
#ifdef _DEBUG
		T* m_object;
#endif
	};

	class GeneralAllocator
	{
	public:
		static const uint8 alignment = 16;

		// TODO: could convert it to template function that takes count(N count of T) as an argument

		template<typename T>
		static ObjectPtr<T> Allocate()
		{
			// size + alignment ensures that there is space for alignment
			size_t objectSize = sizeof(T);
			size_t bufferSize = objectSize + alignment;
			void* notAlignedBase = new uint8[bufferSize];

			void* alignedBase = nullptr;
			if (alignedBase = std::align(alignment, objectSize, notAlignedBase, bufferSize))
			{
				// std::align modifies bufferSize and now: bufferSize is equal to allocated memory 
				// for object + alignment leftovers, so we can move it to ObjectAllocationInfo as 
				// allocationSize parameter

				T* allocatedObject = new (static_cast<uint8*>(alignedBase)) T();
				
				ObjectAllocationInfo<T> allocationInfo;
				allocationInfo.base = notAlignedBase;
				allocationInfo.allocationSize = bufferSize;
				allocationInfo.object = allocatedObject;
				allocationInfo.objectSize = objectSize;

				ObjectPtr<T> objectPtr(allocationInfo);
				objectPtr.

				return ;
			}

			ENGINE_ASSERT(false, "Allocation failed.");
			return ObjectPtr<T>();
		}

		template<typename T>
		static void	Deallocate(ObjectHandle<T>& objHandle)
		{
			if (objHandle)
			{
				ObjectAllocationInfo allocationInfo = objHandle.GetAllocationInfo();
				delete[allocationInfo.allocationSize] allocationInfo.base;
			}
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

		void* operator new(std::size_t) = delete;
		void operator delete(void*) = delete;

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