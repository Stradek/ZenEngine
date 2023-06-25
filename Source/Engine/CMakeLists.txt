#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Include/Engine)

get_source_files(ENGINE_SOURCE_FILES 0 ${SOURCE_DIR})
get_header_files(ENGINE_HEADER_FILES 1 ${INCLUDE_DIR})

#
# Library
#

add_library(Engine
    STATIC
    "${ENGINE_SOURCE_FILES}"
    "${ENGINE_HEADER_FILES}"
)

set_property(TARGET Engine PROPERTY FOLDER "Engine")
target_include_directories(Engine PUBLIC
    "${PROJECT_SOURCE_DIR}/Include"
    "${PROJECT_SOURCE_DIR}/Source/Engine"
)

#
# Dependencies
#

add_subdirectory("Core")
target_link_libraries(Engine PUBLIC Core)

add_subdirectory("Common")
target_link_libraries(Engine PUBLIC Common)

# Example: 
# add_subdirectory("Engine", "../Engine/Core")
# target_link_libraries(Engine PUBLIC Core)
# target_include_directories(Engine PUBLIC
# )
