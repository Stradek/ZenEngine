#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(COMMON_INCLUDE_DIR ${ENGINE_INCLUDE_DIR}/Common)

set(COMMON_INCLUDE_DIR ${COMMON_INCLUDE_DIR} PARENT_SCOPE)

get_source_files(COMMON_SOURCE_FILES 1 ${SOURCE_DIR})
get_header_files(COMMON_HEADER_FILES 1 ${COMMON_INCLUDE_DIR})


set(COMMON_FILES 
    "${COMMON_SOURCE_FILES}"
    "${COMMON_HEADER_FILES}"
)

#
# Library
#

add_library(Common
    STATIC
    "${COMMON_FILES}"
)

set_property(TARGET Common PROPERTY FOLDER "Common")
target_include_directories(Common PRIVATE
    ${COMMON_INCLUDE_DIR}
)

#
# Precompiled Headers
#

target_precompile_headers(Common
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h"
)