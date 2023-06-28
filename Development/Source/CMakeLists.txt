#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

add_subdirectory(Common)

link_libraries(Common)
include_directories(${COMMON_INCLUDE_DIR})

add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(Game)

#
# Precompiled Headers
#

target_precompile_headers(Engine
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h
)

target_precompile_headers(Editor REUSE_FROM Engine)
target_precompile_headers(Game REUSE_FROM Engine)

#
# Targets Additional Settings
#

# Change working directory to top dir to access assets folder
# when using targets that generate executables
set_property(TARGET Editor PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
set_property(TARGET Game PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# Set Game as Visual Studio startup project
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)