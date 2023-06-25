#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

#
# Project Info
#

cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
cmake_policy(VERSION 3.6)

include("Build/CMakeShared.cmake")

project(DX12EngineTest)
custom_cmake_setup()

#
# Sources
#

add_subdirectory(Source)

#
# Environment
#

set(CMAKE_BINARY_DIR                "${CMAKE_SOURCE_DIR}/Binaries")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}")