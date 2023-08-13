/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "Defines.h"

namespace Engine::Common::DateTime
{
	typedef std::chrono::high_resolution_clock					high_res_clock;
	typedef std::chrono::system_clock							system_clock;

	typedef std::chrono::time_point<high_res_clock>				time_point;
	typedef std::chrono::time_point<system_clock>				system_time_point;

	typedef std::chrono::hours									hours;
	typedef std::chrono::minutes								minutes;
	typedef std::chrono::seconds								seconds;
	typedef std::chrono::milliseconds							milliseconds;
	typedef std::chrono::nanoseconds							nanoseconds;

	typedef std::chrono::duration<double, std::ratio<1, 1>>		seconds_duration_from_double;
	typedef std::chrono::duration<uint32, std::nano>			nanoseconds_duration_from_uint32;
}