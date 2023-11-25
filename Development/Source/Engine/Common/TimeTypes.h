/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "Defines.h"

namespace Engine::Common
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
}