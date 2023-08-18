#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

set(INCLUDE_DIR ${ENGINE_INTERNAL_INCLUDE_DIR}/Debug)

#
# Library
#

get_all_target_files(TARGET_FILES 0 ${INCLUDE_DIR})

add_library(Debug
    STATIC
    "${TARGET_FILES}"
)

target_include_directories(Debug PRIVATE
    ${INCLUDE_DIR}
)

#
# Dependencies
#

target_link_libraries(Debug PUBLIC 
    # Engine
    Core
)

target_include_directories(Engine PRIVATE
    ${TRACY_HEADERS}
)

# 
# Precompiled Headers
#

target_precompile_headers(Debug
    PRIVATE
    ${ENGINE_PRECOMILED_HEADER}
)

#
# Visual Studio Configuration
#

set_target_properties(
    Debug
    PROPERTIES 
    FOLDER "Engine"
)