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

add_subdirectory(Engine)
add_subdirectory(Editor)

set_target_properties(Engine Editor
    PROPERTIES
    CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_SOURCE_DIR}/Binaries"
    CMAKE_ARCHIVE_OUTPUT_DIRECTORY  "${CMAKE_SOURCE_DIR}/Binaries"
    CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_SOURCE_DIR}/Binaries"
    CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_SOURCE_DIR}/Binaries"
)