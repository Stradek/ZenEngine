/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

namespace Engine::Core::Memory
{
	// implement SharedAllocatorHandle and UniqueAllocatorHandle that hold references and deallocate automatically
	// implement SafeAllocatorHandle that holds reference and deallocate automatically when all references are gone

	struct ObjectAllocationInfo
	{
		uint8* base;
		size_t allocationSize;

		uint8* object;
		size_t objectSize;
	};

	struct AllocationInfo
	{
		// TODO: 
		// - we should add here bool for allocation validation
		// - refactor that
		// - decouple implementation to class, leave here data only
		uint8* base;
		uint8* firstChunk;
		uint8* lastChunk;
		size_t chunkSize;
		size_t chunkCount;

		AllocationInfo(uint8* base, uint8* firstObject, uint8* lastObject, size_t chunkSize) :
			base(base), firstChunk(firstObject), lastChunk(lastObject), chunkSize(chunkSize)
		{
			uint8 lastChunkAddr = *lastChunk;
			uint8 firstChunkAddr = *firstChunk;

			this->chunkCount = (lastChunkAddr - firstChunkAddr) / chunkSize;
		}
	};

	template<typename T>
	class ObjectPtr
	{
	public:
		ObjectPtr() : m_allocationInfo() {}

		ObjectPtr(const ObjectPtr<T>& objectPtr) : m_allocationInfo(objectPtr.GetAllocationInfo())
#ifdef _DEBUG
			, m_object(reinterpret_cast<T**>(objectPtr.GetAllocationInfo().object))
#endif
		{
		}

		T* Get()
		{
			if (!IsValid())
			{
				return nullptr;
			}

			return reinterpret_cast<T*>(m_allocationInfo.object);
		}

		void Free()
		{
			if (IsValid())
			{
				GeneralAllocator::Deallocate(GetAllocationInfo());
			}
		}

		const ObjectAllocationInfo& GetAllocationInfo() const
		{
			return m_allocationInfo;
		}

		bool IsValid() const
		{
			return GeneralAllocator::ValidateAllocation(GetAllocationInfo());
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
		ObjectAllocationInfo m_allocationInfo;
#ifdef _DEBUG
		T** m_object;
#endif

	protected:
		// This is used to create ObjectPtr and initialize object 
		// It should be used only after Object is created with GeneralAllocator
		ObjectPtr(const ObjectAllocationInfo& allocationInfo) : m_allocationInfo(allocationInfo)
#ifdef _DEBUG
			, m_object(reinterpret_cast<T**>(allocationInfo.object))
#endif
		{
		}

		friend class GeneralAllocator;
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

			ObjectPtr<T>::ObjectPtr(objectPtr);

			return *this;
		}

		template<typename U>
		ScopedObjectPtr(const ObjectPtr<U>& objectPtr) : ObjectPtr<T>(objectPtr.GetAllocationInfo()) {}

		ScopedObjectPtr(const ObjectPtr<T>& objectPtr) : ObjectPtr<T>(objectPtr) {}

		~ScopedObjectPtr()
		{
			Free();
		}

		ScopedObjectPtr(const ScopedObjectPtr<T>& other) = delete;
	};

	template<typename T>
	class ObjectHandle
	{
	public:
		explicit operator bool() const 
		{
			return m_objectPtr.IsValid();
		}

		ObjectHandle() : m_objectPtr()
#ifdef _DEBUG
			,m_object(nullptr)
#endif
		{

		}

		ObjectHandle(const ObjectPtr<T>& objectPtr) :
			m_objectPtr(objectPtr)
#ifdef _DEBUG
			, m_object(objectPtr.Get())
#endif
		{
			ENGINE_ASSERT(objectPtr.IsValid(), "Object is not valid.");
		}

		template<typename U>
		ObjectHandle(const ObjectHandle<U>& otherObjectHandle) : ObjectHandle(other->GetAllocationInfo()) {}

		ObjectHandle(const ObjectHandle<T>& other) : ObjectHandle() {}
		
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
			if (!m_objectPtr.IsValid())
			{
				ENGINE_ASSERT(false, "Object handle is not valid.");
				return nullptr;
			}

			return m_objectPtr.Get();
		}

		ObjectAllocationInfo GetAllocationInfo()
		{
			return m_objectPtr.GetAllocationInfo();

		}

		void* operator new(std::size_t) = delete;
		void operator delete(void*) = delete;

	protected:
		const ObjectPtr<T>& m_objectPtr;
#ifdef _DEBUG
		T* m_object;
#endif
	};

	class GeneralAllocator
	{
	public:
		static const uint8 alignment = 16;
		static std::unordered_map<uint8*, bool> allocationValidationMap;

		// TODO: could convert it to template function that takes count(N count of T) as an argument

		static bool ValidateAllocation(const ObjectAllocationInfo& allocationInfo)
		{
			auto it = allocationValidationMap.find(allocationInfo.base);
			if (it != allocationValidationMap.end())
			{
				return it->second;
			}

			return false;
		}

		template<typename T>
		static ObjectPtr<T> Allocate()
		{
			// size + alignment ensures that there is space for alignment
			size_t objectSize = sizeof(T);
			size_t bufferSize = objectSize + alignment;

			uint8* notAlignedBase = new uint8[bufferSize];
			uint8* alignedBase = nullptr;

			{
				void* notAlignedBaseVoid = static_cast<void*>(notAlignedBase);
				// std::align modifies bufferSize and now: bufferSize is equal to allocated memory 
				// for object + alignment leftovers, so we can move it to ObjectAllocationInfo as 
				// allocationSize parameter
				alignedBase = static_cast<uint8*>(std::align(alignment, objectSize,
					notAlignedBaseVoid, bufferSize));
			}
			


			size_t alignedBaseAddr = reinterpret_cast<size_t>(alignedBase);

			size_t alignmentBitmask = alignment - 1;
			size_t baseAlignmentBits = alignedBaseAddr & alignmentBitmask;

			if (baseAlignmentBits != 0)
			{
				delete[bufferSize] notAlignedBase;
				ENGINE_ASSERT(false, "Allocation failed. Allignment is not correct");

				return ObjectPtr<T>();
			}

			ObjectAllocationInfo allocationInfo;

			allocationInfo.base = notAlignedBase;
			allocationInfo.allocationSize = bufferSize;

			T* allocatedObject = new (static_cast<uint8*>(alignedBase)) T();
			uint8* allocatedObjectAddr = reinterpret_cast<uint8*>(allocatedObject);
			allocationInfo.object = allocatedObjectAddr;
			allocationInfo.objectSize = objectSize;

			ObjectPtr<T> objectPtr(allocationInfo);
			allocationValidationMap.insert(std::make_pair(notAlignedBase, true));

			return objectPtr;
		}

		static void Deallocate(const ObjectAllocationInfo& allocationInfo)
		{
			if (ValidateAllocation(allocationInfo))
			{
				delete[allocationInfo.allocationSize] allocationInfo.base;
				allocationValidationMap.erase(allocationInfo.base);
			}
			else
			{
				ENGINE_ASSERT(false, "Deallocating invalid object.");
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

			uint8* unalignedBase = new uint8[bufferSize];
			if (uint8* aligned = std::align(alignment, allocationSize, &unalignedBase bufferSize))
			{
				uint8* firstObject = aligned;
				uint8* lastObject = aligned + sizeof(T) * count;

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
		//template<typename T>
		//static void	Deallocate(uint8*& obj, size_t count)
		//{
		//	delete[count] reinterpret_cast<T*>(obj);
		//}

		//static void	Deallocate(uint8*& obj, size_t byteSize)
		//{
		//	delete[byteSize] reinterpret_cast<uint8*>(obj);
		//}
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

			uint8* chunk = m_freeList.Get();

			uint8* nextChunk = *(reinterpret_cast<T**>(m_freeList.Get()));
			m_freeList = nextChunk.Get();

			return reinterpret_cast<T*>(chunk);
		}

		// implement Shared/Unique/Safe AllocatorHandle to deallocate automatically and call 
		// this function on it's destructor
		void Deallocate(uint8* chunk)
		{
			*chunk = m_freeList.Get();
			m_freeList = chunk.Get();
		}

		void* operator new(std::size_t) = delete;
		void operator delete(void*) = delete;

	private:
		AllocationInfo allocationInfo;
		uint8* m_freeList;
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