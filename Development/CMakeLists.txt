#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Targets Configuration
#

# Engine
set(MAIN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Include)
set(MAIN_ENGINE_INCLUDE_DIR ${MAIN_INCLUDE_DIR}/Engine)

# External
set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/External)

# Dependencies

# spdlog
set(SPDLOG_ROOT ${EXTERNAL_DIR}/spdlog)

# fmt
set(FMT_ROOT ${EXTERNAL_DIR}/fmt)

# tracy
set(TRACY_ROOT ${EXTERNAL_DIR}/tracy)
set(TRACY_HEADERS ${TRACY_ROOT}/public)
set(TRACY_DEPENDENCIES_ROOT ${EXTERNAL_DIR}/tracy_dependencies)
set(TRACY_DEPENDENCIES_HEADERS ${TRACY_DEPENDENCIES_ROOT}/include)

# SDL
set(SDL_ROOT ${EXTERNAL_DIR}/SDL)

#
# Programs
#

add_subdirectory(Programs/TracyProfilerTool)

#
# Sources
#

add_subdirectory(Source)

