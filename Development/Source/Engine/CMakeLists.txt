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
target_link_libraries(Engine PUBLIC Common)

add_subdirectory("Core")
target_link_libraries(Engine PUBLIC Core)

target_precompile_headers(Core REUSE_FROM Engine)