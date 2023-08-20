#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(INCLUDE_DIR ${ENGINE_INTERNAL_INCLUDE_DIR}/Core)

#
# Library
#

get_all_target_files(TARGET_FILES 0 ${INCLUDE_DIR})

add_library(Core
    STATIC
    "${TARGET_FILES}"
)

set_property(TARGET Core PROPERTY FOLDER "Engine")
target_include_directories(Core PRIVATE
    ${INCLUDE_DIR}
)

# This needs to be always here as it makes every
# include in engine start with <Engine/...>
target_include_directories(Core PUBLIC
    ${ENGINE_INCLUDE_DIR_CORE}
)

#
# Dependencies
#

target_link_libraries(Core PUBLIC 
    # Engine
    Common

    # External 
    spdlog fmt 

    # Internal 
    TracyProfilerClient
)

# 
# Precompiled Headers
#

target_precompile_headers(Core PRIVATE
    ${ENGINE_PRECOMILED_HEADER}
)