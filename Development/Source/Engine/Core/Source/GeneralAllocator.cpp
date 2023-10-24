/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "GeneralAllocator.h"
#include "MemoryConfig.h"

namespace Engine::Memory 
{
	/*
	* Allocated memory consists of:
	* 1. (optionally) Unaligned memory - buffer used to align memory after allocation	[size: alignment - 1]
	* 2. Pointer to unalignedPtr - used to free whole memory block						[size: sizeof(void*)]
	* 3. Aligned memory - memory aligned to alignment									[size: size]
	* 
	* Returned pointer points to 3
	* During Free() we need to retrieve pointer to 1 to free full memory block.
	*/
	void* GeneralAllocator::Allocate(const size_t size, const size_t alignment)
	{
		uint fullAllocationSize = size + alignment + sizeof(void*);
		void* unalignedPtr = malloc(fullAllocationSize);
		if (unalignedPtr == nullptr)
		{
			ENGINE_ERROR("Failed to allocate memory.");
			return nullptr; // Return nullptr if allocation fails
		}

		void* alignedPtrAddr = (void*) (((size_t)unalignedPtr + alignment + sizeof(void*) - 1) & ~(alignment - 1));
		*(static_cast<void**>(alignedPtrAddr)) = &unalignedPtr;
	
		void* allocatedObjectPtr = static_cast<char*>(alignedPtrAddr) + sizeof(void*); // Use static_cast to avoid pointer arithmetic on void*
		return allocatedObjectPtr;
	}

	void GeneralAllocator::Free(void* ptr)
	{
		void* alignedPtrAddr = static_cast<char*>(ptr) - sizeof(void*);
		void* unalignedPtr = *(static_cast<void**>(alignedPtrAddr));

		free(unalignedPtr);
	}
}