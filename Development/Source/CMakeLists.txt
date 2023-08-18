#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

set(ENGINE_PRECOMILED_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h)

#
# Dependencies
#

add_subdirectory(Engine)

#
# Applications
#

add_subdirectory(Editor)
add_subdirectory(Game)

# Game & Editor precompiled headers inheritance from engine
target_precompile_headers(Editor REUSE_FROM Engine)
target_precompile_headers(Game REUSE_FROM Engine)

#
# Targets Additional Settings
#

# Change working directory to top dir to access assets folder for executable targets
set_target_properties(Editor Game
    PROPERTIES 
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Set Game as Visual Studio startup project
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)
