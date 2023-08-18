#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(GRAPHICS_INCLUDE_DIR ${ENGINE_INCLUDE_DIR}/Graphics)

set(GRAPHICS_INCLUDE_DIR ${GRAPHICS_INCLUDE_DIR} PARENT_SCOPE)

get_source_files(GRAPHICS_SOURCE_FILES 0 ${SOURCE_DIR})
get_header_files(GRAPHICS_HEADER_FILES 0 ${GRAPHICS_INCLUDE_DIR})

set(GRAPHICS_FILES 
    "${GRAPHICS_SOURCE_FILES}"
    "${GRAPHICS_HEADER_FILES}"
)

#
# Library
#

add_library(Graphics
    STATIC
    "${GRAPHICS_FILES}"
)

set_property(TARGET Graphics PROPERTY FOLDER "Engine")
target_include_directories(Graphics PRIVATE
    ${GRAPHICS_INCLUDE_DIR}
        
    # Dependencies
    ${ENGINE_INCLUDE_DIR}
)

#
# Dependencies
#

# Engine dependencies
target_link_libraries(Graphics PRIVATE Core Debug)

# SDL library
target_link_libraries(Graphics PUBLIC SDL2)
target_include_directories(Graphics PRIVATE
    ${SDL_ROOT}/include
)

# 
# Precompiled Headers
#

target_precompile_headers(Graphics
    PRIVATE
    ${ENGINE_PRECOMILED_HEADER}
)