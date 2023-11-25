#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Dependencies
#

# External
set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/External)

include(${EXTERNAL_DIR}/fmt.cmake)
include(${EXTERNAL_DIR}/sdl.cmake)
include(${EXTERNAL_DIR}/spdlog.cmake)
include(${EXTERNAL_DIR}/tracy.cmake)

# Internal
set(INTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Internal)

include(${INTERNAL_DIR}/tracy_profiler_client.cmake)

#
# Sources
#

add_subdirectory(Source)
