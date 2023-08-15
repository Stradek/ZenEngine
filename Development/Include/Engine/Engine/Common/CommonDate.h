/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

namespace Engine::Common::DateTime
{
	struct Date
	{
		int year;
		int month;
		int day;
	};

	extern Date GetCurrentDate();
}
