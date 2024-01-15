/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <chrono>

namespace Engine::Common
{
    struct Time
    {
        using Clock = std::chrono::high_resolution_clock;
        using Duration = Clock::duration;
        using TimePoint = Clock::time_point;

        using Seconds = std::chrono::seconds;
        using Miliseconds = std::chrono::milliseconds;
        using Microseconds = std::chrono::microseconds;
        using Nanoseconds = std::chrono::nanoseconds;
        
        template<class DurationUnit>
        static DurationUnit DurationCast(const Duration& d)
        {
            return std::chrono::duration_cast<DurationUnit>(d);
        }

        template<typename ReturnType, class DurationUnit>
        static ReturnType DurationCast(const Duration& d)
        {
            DurationUnit duration = std::chrono::duration_cast<DurationUnit>(d);
            return duration.count();
        }

        static TimePoint GetTimeNow();
    };
}