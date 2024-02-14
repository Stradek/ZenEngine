/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <chrono>

namespace Engine::Common
{
    class Date
    {
    public:
        static tm GetLocalTime();
    };
}