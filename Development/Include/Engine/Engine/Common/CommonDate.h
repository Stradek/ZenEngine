/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

namespace Engine::Common
{
	class Date
	{
	public:
		Date(std::time_t timeNow);

		size_t GetYear() const;
		size_t GetMonth() const;
		size_t GetDay() const;
	private:
		tm m_timeInfo;
	};

	extern Date GetCurrentDate();
}
