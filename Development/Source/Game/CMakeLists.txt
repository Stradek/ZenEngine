#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Files
#

#############################################################
#                       !WARNING!                           #
#                                                           #
# get_all_target_files second parameter is USE_RECURSE      #
# I set it to 1 to get all files in subfolders              #
# Game probabably won't have more than 1 target.            #
# In case I will change my mind it's worth looking into.    #
#############################################################

get_all_target_files(TARGET_FILES 1 ${CMAKE_CURRENT_SOURCE_DIR})

#
# Executable
#

add_executable(Game
    "${TARGET_FILES}"
)

target_include_directories(Game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

#
# Internal Dependencies
#

target_link_libraries(Game PRIVATE 
    Engine 
)

#
# Post Build
#

add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${SDL_DLL} $<TARGET_FILE_DIR:Game>
)

#
# Visual Studio Configuration
#

set_target_properties(
    Game
    PROPERTIES 
    FOLDER "Game"
)