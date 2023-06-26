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

# Setting up custom properties and functions from "CMakeShared.cmake" file
custom_cmake_setup()

#
# Sources
#

add_subdirectory(Source)