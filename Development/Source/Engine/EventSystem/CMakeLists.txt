#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

set(INCLUDE_DIR ${ENGINE_INTERNAL_INCLUDE_DIR}/EventSystem)


#
# Library
#

get_all_target_files(TARGET_FILES 0 ${INCLUDE_DIR})

add_library(EventSystem
    STATIC
    "${TARGET_FILES}"
)

target_include_directories(EventSystem PRIVATE
    ${INCLUDE_DIR}
)

#
# Dependencies
#

target_link_libraries(EventSystem PUBLIC 
    # Engine
    Core Debug

    # External
    SDL2
)

# 
# Precompiled Headers
#

target_precompile_headers(EventSystem
    PRIVATE
    ${ENGINE_PRECOMILED_HEADER}
)

#
# Visual Studio Configuration
#

set_target_properties(
    EventSystem
    PROPERTIES 
    FOLDER "Engine"
)