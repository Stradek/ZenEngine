#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(Game)

set(PRECOMPILED_HEADERS 
    "${CMAKE_SOURCE_DIR}/Include/Precompiled.h"
)

target_precompile_headers(Engine
    PRIVATE 
    "${PRECOMPILED_HEADERS}"
    "${CMAKE_SOURCE_DIR}/Include/Common/Common.h"
)

target_precompile_headers(Editor
    PRIVATE 
    "${PRECOMPILED_HEADERS}"
)

target_precompile_headers(Game
    PRIVATE 
    "${PRECOMPILED_HEADERS}"
)