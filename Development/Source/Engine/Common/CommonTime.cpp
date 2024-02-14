/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "CommonTime.h"

namespace Engine::Common
{
    TimePoint TimePoint::GetTimeNow()
    {
        TimePoint timeStruct();
        return ChronoHighResClock::now();
    }
    
    uint Duration::GetSeconds()
    {
        return m_duration.count() / 1,000,000,000;
    }

    uint Duration::GetMilliseconds()
    {
        return m_duration.count() / 1,000,000;
    }
    uint Duration::GetNanoseconds()
    {
        return m_duration.count();
    }
}