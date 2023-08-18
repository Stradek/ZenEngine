#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

set(INCLUDE_DIR ${ENGINE_INTERNAL_INCLUDE_DIR}/Common)

#
# Library
#

get_all_target_files(TARGET_FILES 1 ${INCLUDE_DIR})

add_library(Common
    STATIC
    "${TARGET_FILES}"
)

target_include_directories(Common PUBLIC
    ${INCLUDE_DIR}
)

#
# Dependencies
#

target_link_libraries(Common PRIVATE 
    # Internal
    TracyProfilerClient
)

#
# Precompiled Headers
#

target_precompile_headers(Common
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h"
)

#
# Visual Studio Configuration
#

set_target_properties(
    Common
    PROPERTIES 
    FOLDER "Engine"
)