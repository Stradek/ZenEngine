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
# Engine Library
#

add_subdirectory(Engine)

#
# Application Executables
#

add_subdirectory(Editor)
add_subdirectory(Game)

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
