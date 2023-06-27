#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(CORE_INCLUDE_DIR ${ENGINE_INCLUDE_DIR}/Core)

set(CORE_INCLUDE_DIR ${CORE_INCLUDE_DIR} PARENT_SCOPE)

get_source_files(CORE_SOURCE_FILES 0 ${SOURCE_DIR})
get_header_files(CORE_HEADER_FILES 0 ${CORE_INCLUDE_DIR})

set(CORE_FILES 
    "${CORE_SOURCE_FILES}"
    "${CORE_HEADER_FILES}"
)

#
# Library
#

add_library(Core
    STATIC
    "${CORE_FILES}"
)

set_property(TARGET Core PROPERTY FOLDER "Engine")
target_include_directories(Core PUBLIC
    ${CORE_INCLUDE_DIR}
)

#
# Dependencies
#

#
# Precompiled Headers
#

