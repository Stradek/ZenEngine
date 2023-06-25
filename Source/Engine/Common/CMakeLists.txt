#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Include/Common)

get_source_files(COMMON_SOURCE_FILES 0 ${SOURCE_DIR})
get_header_files(COMMON_HEADER_FILES 1 ${INCLUDE_DIR})

#
# Library
#

add_library(Common
    STATIC
    "${COMMON_SOURCE_FILES}"
    "${COMMON_HEADER_FILES}"
)

set_property(TARGET Common PROPERTY FOLDER "Engine")
target_include_directories(Common PUBLIC
    "${PROJECT_SOURCE_DIR}/Include"
    "${PROJECT_SOURCE_DIR}/Source/Engine"
)

# Use the retrieved precompiled headers for the child target
target_precompile_headers(Common REUSE_FROM Engine)