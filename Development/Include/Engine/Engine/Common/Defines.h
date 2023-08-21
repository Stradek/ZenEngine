/*
    Copyright (c) 2023 Piotr Stradowski. All rights reserved.
    Software distributed under the permissive MIT License.
*/

#pragma once

/*
    Data Types
*/

using uint      = unsigned int;

using uint8     = std::uint8_t;
using uint16    = std::uint16_t;
using uint32    = std::uint32_t;
using uint64    = std::uint64_t;

/*
    Configuration
*/

#if defined(CMAKE_CONFIG_DEBUG)
    #define CONFIG_DEBUG 
    #define CONFIG_CURRENT "Debug"
#elif defined(CMAKE_CONFIG_RELEASE)
    #define CONFIG_RELEASE 
    #define CONFIG_CURRENT "Release"
#else
    #error Unknown configuration!
#endif