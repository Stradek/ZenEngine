/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once
#include "IAllocator.h"

namespace Engine::Core::Memory
{
	template <typename Type>
	class LinearAllocator : IAllocator<Type>
	{
	};
}