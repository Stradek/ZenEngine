#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(ENGINE_INCLUDE_DIR ${MAIN_INCLUDE_DIR}/Engine/Engine)

# Please...don't set here ENGINE_INCLUDE_DIR to PARENT_SCOPE
#                         ^^^^^^^^^^^^^ NEVER ^^^^^^^^^^^^^^

get_source_files(ENGINE_SOURCE_FILES 0 ${SOURCE_DIR})
get_header_files(ENGINE_HEADER_FILES 0 ${ENGINE_INCLUDE_DIR})

set(ENGINE_FILES 
    "${ENGINE_SOURCE_FILES}"
    "${ENGINE_HEADER_FILES}"
)

#
# Library
#

add_library(Engine
    STATIC
    "${ENGINE_FILES}"
)

set_property(TARGET Engine PROPERTY FOLDER "Engine")
target_include_directories(Engine PUBLIC
    ${ENGINE_INCLUDE_DIR}
)

#
# Dependencies
#

add_subdirectory("Common")
add_subdirectory("Core")
add_subdirectory("Debug")

# Engine dependencies
target_link_libraries(Engine PUBLIC Core Common Debug)

# Tracy dependency
add_compile_definitions(
    "$<$<CONFIG:Debug>:TRACY_ENABLE>"
)

target_link_libraries(Engine PRIVATE TracyProfilerClient)
target_include_directories(Engine PRIVATE
    ${TRACY_HEADERS}
)

#
# Precompiled Headers
#

target_precompile_headers(Engine
    PRIVATE
    ${ENGINE_PRECOMILED_HEADER}
)