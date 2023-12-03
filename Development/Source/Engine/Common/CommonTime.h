/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "TimeTypes.h"
#include "Defines.h"

namespace Engine::Common
{
	static constexpr uint64 HOUR_TO_NANOSECOND = static_cast<uint64>(std::chrono::nanoseconds(std::chrono::hours(1)).count());
	static constexpr uint64 MINUTE_TO_NANOSECOND = static_cast<uint64>(std::chrono::nanoseconds(std::chrono::minutes(1)).count());
	static constexpr uint64 SECOND_TO_NANOSECOND = static_cast<uint64>(std::chrono::nanoseconds(std::chrono::seconds(1)).count());
	static constexpr uint64 MILISECOND_TO_NANOSECOND = static_cast<uint64>(std::chrono::nanoseconds(std::chrono::milliseconds(1)).count());

	static constexpr double NANOSECOND_TO_HOUR = 1.0 / HOUR_TO_NANOSECOND;
	static constexpr double NANOSECOND_TO_MINUTE = 1.0 / MINUTE_TO_NANOSECOND;
	static constexpr double NANOSECOND_TO_SECOND = 1.0 / SECOND_TO_NANOSECOND;
	static constexpr double NANOSECOND_TO_MILLISECOND = 1.0 / MILISECOND_TO_NANOSECOND;

	class Time
	{
	public:
		Time(uint64 timeInNanoseconds) : m_nanosecondTime(timeInNanoseconds) {}

		static Time GetTimeNow();

		static Time Duration(const Time& start, const Time& end) { return Time(end.GetNanoseconds() - start.GetNanoseconds()); }
		
		inline bool operator<(const Time& other) const { return m_nanosecondTime < other.m_nanosecondTime; }
		inline bool operator>(const Time& other) const { return m_nanosecondTime > other.m_nanosecondTime; }
		inline bool operator<=(const Time& other) const { return m_nanosecondTime <= other.m_nanosecondTime; }
		inline bool operator>=(const Time& other) const { return m_nanosecondTime >= other.m_nanosecondTime; }

		uint64 GetRawTime() const { return GetNanoseconds(); }
		uint64 GetNanoseconds() const;

		double GetHours() const;
		double GetMinutes() const;
		double GetSeconds() const;
		double GetMilliseconds() const;
	private:
		uint64 m_nanosecondTime;
	};

}