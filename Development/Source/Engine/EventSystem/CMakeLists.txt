#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(EVENT_SYSTEM_INCLUDE_DIR ${ENGINE_INCLUDE_DIR}/EventSystem)

set(EVENT_SYSTEM_INCLUDE_DIR ${EVENT_SYSTEM_INCLUDE_DIR} PARENT_SCOPE)

get_source_files(EVENT_SYSTEM_SOURCE_FILES 0 ${SOURCE_DIR})
get_header_files(EVENT_SYSTEM_HEADER_FILES 0 ${EVENT_SYSTEM_INCLUDE_DIR})

set(EVENT_SYSTEM_FILES 
    "${EVENT_SYSTEM_SOURCE_FILES}"
    "${EVENT_SYSTEM_HEADER_FILES}"
)

#
# Library
#

add_library(EventSystem
    STATIC
    "${EVENT_SYSTEM_FILES}"
)

set_property(TARGET EventSystem PROPERTY FOLDER "Engine")
target_include_directories(EventSystem PRIVATE
    ${EVENT_SYSTEM_INCLUDE_DIR}
        
    # Dependencies
    ${ENGINE_INCLUDE_DIR}
)

#
# Dependencies
#

# Engine dependencies
target_link_libraries(EventSystem PRIVATE Core Debug)

# SDL library
target_link_libraries(EventSystem PUBLIC SDL2)
target_include_directories(EventSystem PRIVATE
    ${SDL_ROOT}/include
)

# 
# Precompiled Headers
#

target_precompile_headers(EventSystem
    PRIVATE
    ${ENGINE_PRECOMILED_HEADER}
)