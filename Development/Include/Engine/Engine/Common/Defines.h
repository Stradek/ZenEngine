/*
    Copyright (c) 2023 Piotr Stradowski. All rights reserved.
    Software distributed under the permissive MIT License.
*/

#pragma once

/*
    Data Types
*/

typedef unsigned int uint;

typedef std::uint8_t uint8;
typedef std::uint16_t uint16_t;
typedef std::uint32_t uint32;
typedef std::uint64_t uint64;

/*
    Configuration
*/

#if defined(CMAKE_CONFIG_DEBUG)
    #define CONFIG_DEBUG "Debug"
    #define CONFIG_CURRENT CONFIG_DEBUG
#elif defined(CMAKE_CONFIG_RELEASE)
    #define CONFIG_RELEASE "Release"
    #define CONFIG_CURRENT CONFIG_RELEASE
#else
    #error Unknown configuration!
#endif