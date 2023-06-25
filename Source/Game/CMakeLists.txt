#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Include/Game)

get_source_files(GAME_SOURCE_FILES 0 ${SOURCE_DIR})
get_header_files(GAME_HEADER_FILES 1 ${INCLUDE_DIR})

#
# Library
#

add_executable(Game
    "${GAME_SOURCE_FILES}"
    "${GAME_HEADER_FILES}"
)

set_property(TARGET Game PROPERTY FOLDER "Game")
target_include_directories(Game PUBLIC
    "${PROJECT_SOURCE_DIR}/Include"
    "${PROJECT_SOURCE_DIR}/Source/Game"
    "${PROJECT_SOURCE_DIR}/Source/Engine"
)

#
# Dependencies
#

target_link_libraries(Game PUBLIC Engine)

#
# Finish Settings
#

# Change working directory to top dir to access assets folder
set_property(TARGET Game PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# Set Game as Visual Studio startup project
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)
