#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(INCLUDE_DIR ${ENGINE_INTERNAL_INCLUDE_DIR}/WindowManagement)


#
# Library
#

get_all_target_files(TARGET_FILES 1 ${INCLUDE_DIR})

add_library(WindowManagement
    STATIC
    "${TARGET_FILES}"
)

target_include_directories(WindowManagement PRIVATE
    ${INCLUDE_DIR}
)

#
# Dependencies
#

target_link_libraries(WindowManagement PUBLIC
    # Engine
    Core Debug

    # External
    SDL2
)

# 
# Precompiled Headers
#

target_precompile_headers(WindowManagement
    PRIVATE
    ${ENGINE_PRECOMILED_HEADER}
)

#
# Visual Studio Configuration
#

set_target_properties(
    WindowManagement
    PROPERTIES 
    FOLDER "Engine"
)