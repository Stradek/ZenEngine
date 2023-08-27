#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Files
#

set(INCLUDE_DIR ${ENGINE_INTERNAL_INCLUDE_DIR}/Core)

get_all_target_files(TARGET_FILES 0 ${INCLUDE_DIR})

#
# Library
#

add_library(Core
    STATIC
    "${TARGET_FILES}"
)

target_include_directories(Core PRIVATE
    ${INCLUDE_DIR}
)

# This needs to be always here as it makes every
# include in engine start with <Engine/...>
target_include_directories(Core PUBLIC
    ${ENGINE_INCLUDE_DIR_CORE}
)

#
# Internal Dependencies
#

target_link_libraries(Core PUBLIC 
    # Engine
    Common

    # Internal 
    $<$<CONFIG:Debug>:TracyProfilerClient>
)


#
# External Dependencies
#

target_link_libraries(Core PUBLIC 
    ${FMT_LIB}
)

target_include_directories(Core PUBLIC 
    ${FMT_INCLUDE_DIR}
    ${SPDLOG_INCLUDE_DIR}
)


# 
# Precompiled Headers
#

target_precompile_headers(Core PUBLIC
    ${ENGINE_PRECOMILED_HEADER}
)

#
# Visual Studio Configuration
#

set_target_properties(
    Core
    PROPERTIES 
    FOLDER "Engine"
)
