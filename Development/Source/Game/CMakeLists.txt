#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(GAME_INCLUDE_DIR ${MAIN_INCLUDE_DIR}/Game)

set(GAME_INCLUDE_DIR ${GAME_INCLUDE_DIR} PARENT_SCOPE)


# !WARNING!
#
# get_source_files second parameter is USE_RECURSE
# I set here USE_RECURSE to 1 to get all files in 
# subfolders because Game probabably won't have more
# than 1 target per Game.
#
# In case I will change my mind it's worth looking into
#

get_source_files(GAME_SOURCE_FILES 1 ${SOURCE_DIR})
get_header_files(GAME_HEADER_FILES 1 ${GAME_INCLUDE_DIR})

set(GAME_FILES 
    "${GAME_SOURCE_FILES}"
    "${GAME_HEADER_FILES}"
)

#
# Library
#

add_executable(Game
    "${GAME_FILES}"
)

set_property(TARGET Game PROPERTY FOLDER "Game")
target_include_directories(Game PRIVATE
    ${GAME_INCLUDE_DIR}
)

#
# Dependencies
#

# Engine
target_link_libraries(Game PRIVATE Engine)
target_include_directories(Game PRIVATE
    ${MAIN_ENGINE_INCLUDE_DIR}
)