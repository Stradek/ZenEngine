/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "CommonDate.h"
#include "CommonTime.h"

namespace Engine::Common
{


    class DateTime
    {
    public:
        DateTime(timespec timeInfo);

        static DateTime GetCurrentDateTime();

        Date GetDate() const;
        Time GetTime() const;

        static constexpr uint64 HOUR_TO_NANOSECOND = static_cast<uint64>(std::chrono::nanoseconds(std::chrono::hours(1)).count());
        static constexpr uint64 MINUTE_TO_NANOSECOND = static_cast<uint64>(std::chrono::nanoseconds(std::chrono::minutes(1)).count());
        static constexpr uint64 SECOND_TO_NANOSECOND = static_cast<uint64>(std::chrono::nanoseconds(std::chrono::seconds(1)).count());
        static constexpr uint64 MILISECOND_TO_NANOSECOND = static_cast<uint64>(std::chrono::nanoseconds(std::chrono::milliseconds(1)).count());

        static constexpr double NANOSECOND_TO_HOUR = 1.0 / HOUR_TO_NANOSECOND;
        static constexpr double NANOSECOND_TO_MINUTE = 1.0 / MINUTE_TO_NANOSECOND;
        static constexpr double NANOSECOND_TO_SECOND = 1.0 / SECOND_TO_NANOSECOND;
        static constexpr double NANOSECOND_TO_MILLISECOND = 1.0 / MILISECOND_TO_NANOSECOND;
    private:
        timespec m_timeInfo;
    }
}