#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Files
#

set(INCLUDE_DIR ${ENGINE_INTERNAL_INCLUDE_DIR}/Graphics)

get_all_target_files(TARGET_FILES 1 ${INCLUDE_DIR})

#
# Library
#

add_library(Graphics STATIC
    "${TARGET_FILES}"
)

target_include_directories(Graphics PRIVATE
    ${INCLUDE_DIR}
)

#
# Dependencies
#

target_link_libraries(Graphics PUBLIC
    # Engine
    Core Debug

    # External
    SDL2
)

#
# Visual Studio Configuration
#

set_target_properties(Graphics
    PROPERTIES 
    FOLDER "Engine"
)