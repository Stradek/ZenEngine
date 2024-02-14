/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "Defines.h"

#include <chrono>

namespace Engine::Common
{
    using ChronoHighResClock = std::chrono::high_resolution_clock;
    using ChronoTimePoint = std::chrono::time_point<ChronoHighResClock>;
    using ChronoDuration = std::chrono::duration<uint64_t, std::nano>;

    namespace Time
    {
        class Duration
        {
        public:
            Duration() = default;
            Duration(const Duration& d) = default;
            Duration(const ChronoDuration& duration) : m_duration(duration) {}

            uint GetSeconds();
            uint GetMilliseconds();
            uint GetNanoseconds();

        private:
            ChronoDuration m_duration;
        };

        struct TimePoint
        {
        public:
            TimePoint() = default;
            TimePoint(const TimePoint& t) = default;
            TimePoint(const ChronoTimePoint& timepoint) : m_timepoint(timepoint) {}

            Duration operator-(const TimePoint& t) const { return Duration(m_timepoint - t.m_timepoint); }

            bool IsZero() const { return m_timepoint.time_since_epoch() == ChronoDuration::zero(); }
            
        private:
            ChronoTimePoint m_timepoint;
        };

        static TimePoint GetTimeNow();
    }
}