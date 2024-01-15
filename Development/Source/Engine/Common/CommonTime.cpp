/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "CommonTime.h"

namespace Engine::Common
{
    Time::TimePoint Time::GetTimeNow()
    {
        return Clock::now();
    }
}