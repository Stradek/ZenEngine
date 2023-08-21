/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "Defines.h"

namespace Engine::Common::DateTime
{
	using high_res_clock	= std::chrono::high_resolution_clock;
	using system_clock		= std::chrono::system_clock;

	using time_point		= std::chrono::time_point<high_res_clock>;
	using system_time_point = std::chrono::time_point<system_clock>;

	using hours			= std::chrono::hours;
	using minutes		= std::chrono::minutes;
	using seconds		= std::chrono::seconds;
	using milliseconds	= std::chrono::milliseconds;
	using nanoseconds	= std::chrono::nanoseconds;

	using seconds_duration_from_double		= std::chrono::duration<double, std::ratio<1, 1>>;
	using nanoseconds_duration_from_uint32	= std::chrono::duration<uint32, std::nano>;
}