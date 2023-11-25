#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Files
#

get_all_target_files(TARGET_FILES 1 ${CMAKE_CURRENT_SOURCE_DIR})

#
# Library
#

add_library(WindowManagement STATIC
    "${TARGET_FILES}"
)

target_include_directories(WindowManagement PRIVATE
    ${ENGINE_SOURCE_DIR}
)

#
# Internal Dependencies
#

target_link_libraries(WindowManagement PUBLIC
    # Engine
    Core Debug
)

#
# External Dependencies
#

target_link_libraries(WindowManagement PUBLIC 
    ${SDL_LIB}
)

target_include_directories(WindowManagement PUBLIC
    ${SDL_INCLUDE_DIR}
)

#
# Visual Studio Configuration
#

set_target_properties(WindowManagement
    PROPERTIES 
    FOLDER "Engine"
)