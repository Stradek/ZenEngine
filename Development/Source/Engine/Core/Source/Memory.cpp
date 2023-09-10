/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "Memory.h"

namespace Engine::Core::Memory
{
	std::unordered_map<uint8*, bool> GeneralAllocator::allocationValidationMap = std::unordered_map<uint8*, bool>();
}