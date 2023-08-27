#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Files
#

set(INCLUDE_DIR ${ENGINE_INTERNAL_INCLUDE_DIR}/EventSystem)

get_all_target_files(TARGET_FILES 0 ${INCLUDE_DIR})

#
# Library
#

add_library(EventSystem STATIC
    "${TARGET_FILES}"
)

target_include_directories(EventSystem PRIVATE
    ${INCLUDE_DIR}
)

#
# Internal Dependencies
#

target_link_libraries(EventSystem PUBLIC 
    # Engine
    Core Debug
)

#
# External Dependencies
#

target_link_libraries(EventSystem PUBLIC 
    ${SDL_LIB}
)

target_include_directories(EventSystem PUBLIC
    ${SDL_INCLUDE_DIR}
)

#
# Visual Studio Configuration
#

set_target_properties(EventSystem
    PROPERTIES 
    FOLDER "Engine"
)