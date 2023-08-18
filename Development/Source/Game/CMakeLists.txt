#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

set(INCLUDE_DIR ${MAIN_INCLUDE_DIR}/Game)

#############################################################
#                       !WARNING!                           #
#                                                           #
# get_all_target_files second parameter is USE_RECURSE      #
# I set it to 1 to get all files in subfolders              #
# Game probabably won't have more than 1 target.            #
# In case I will change my mind it's worth looking into.    #
#############################################################

#
# Executable
#

get_all_target_files(TARGET_FILES 1 ${INCLUDE_DIR})

add_executable(Game
    "${TARGET_FILES}"
)

target_include_directories(Game PRIVATE
    ${INCLUDE_DIR}
)

#
# Dependencies
#

target_link_libraries(Game PRIVATE 
    Engine 
)

#
# Visual Studio Configuration
#

set_target_properties(
    Game
    PROPERTIES 
    FOLDER "Game"
)