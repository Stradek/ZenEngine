#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Include/Core)

get_source_files(CORE_SOURCE_FILES 0 ${SOURCE_DIR})
get_header_files(CORE_HEADER_FILES 1 ${INCLUDE_DIR})

#
# Library
#

add_library(Core
    STATIC
    "${CORE_SOURCE_FILES}"
    "${CORE_HEADER_FILES}"
)

set_property(TARGET Core PROPERTY FOLDER "Engine")
target_include_directories(Core PUBLIC
    "${PROJECT_SOURCE_DIR}/Include"
    "${PROJECT_SOURCE_DIR}/Source/Engine"
)

# Use the retrieved precompiled headers for the child target
target_precompile_headers(Core REUSE_FROM Engine)