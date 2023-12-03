/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

namespace Engine::Common
{
    DateTime::DateTime(timespec timeInfo) {
        m_timeInfo = timeInfo;
    }

    static DateTime DateTime::GetCurrentDateTime() {
        m_timeInfo.tv_sec = high_res_clock::now().time_since_epoch();
        m_timeInfo.tv_nsec = 0;
    }

    Date DateTime::GetDate() const {
        tm date(m_timeInfo.tv_sec)
        return date;
    }

    double DateTime::GetHours() const
	{
		return GetNanoseconds() * NANOSECOND_TO_HOUR;
	}

	double DateTime::GetMinutes() const
	{
		return GetNanoseconds() * NANOSECOND_TO_MINUTE;
	}

	double DateTime::GetSeconds() const
	{
		return GetNanoseconds() * NANOSECOND_TO_SECOND;
	}

	double DateTime::GetMilliseconds() const
	{
		return GetNanoseconds() * NANOSECOND_TO_MILLISECOND;
	}

	long long DateTime::GetNanoseconds() const
	{
		return m_timeInfo.tv_nsec;
	}

    Time DateTime::GetTime() const {
        m_timeInfo.tv_sec.count();
    }
}
