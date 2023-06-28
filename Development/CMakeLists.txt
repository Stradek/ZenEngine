#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Targets Configuration
#

set(MAIN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Include)
set(MAIN_ENGINE_INCLUDE_DIR ${MAIN_INCLUDE_DIR}/Engine)

set(SPDLOG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/External/spdlog)

set(DEPENDENCIES_INCLUDE_DIR 
    "${CMAKE_CURRENT_SOURCE_DIR}/External/spdlog"
)

#
# Sources
#

add_subdirectory(Source)