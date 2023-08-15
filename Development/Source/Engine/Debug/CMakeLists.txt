#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(DEBUG_INCLUDE_DIR ${ENGINE_INCLUDE_DIR}/Debug)

set(DEBUG_INCLUDE_DIR ${DEBUG_INCLUDE_DIR} PARENT_SCOPE)

get_source_files(DEBUG_SOURCE_FILES 0 ${SOURCE_DIR})
get_header_files(DEBUG_HEADER_FILES 0 ${DEBUG_INCLUDE_DIR})

set(DEBUG_FILES 
    "${DEBUG_SOURCE_FILES}"
    "${DEBUG_HEADER_FILES}"
)

#
# Library
#

add_library(Debug
    STATIC
    "${DEBUG_FILES}"
)

set_property(TARGET Debug PROPERTY FOLDER "Engine")
target_include_directories(Debug PUBLIC
    ${DEBUG_INCLUDE_DIR}
        
    # Dependencies
    ${ENGINE_INCLUDE_DIR}
)

#
# Dependencies
#

# Engine dependencies
target_link_libraries(Debug PUBLIC Common Core)

# 
# Precompiled Headers
#

target_precompile_headers(Debug
    PRIVATE
    ${ENGINE_PRECOMILED_HEADER}
)