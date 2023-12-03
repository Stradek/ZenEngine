#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Files
#

get_all_target_files(TARGET_FILES 0 ${CMAKE_CURRENT_SOURCE_DIR})

#
# Include Dependencies
#


#
# Library
#

add_library(Core STATIC
    "${TARGET_FILES}"
)

target_include_directories(Core PRIVATE
    ${ENGINE_SOURCE_DIR}
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
    ${ENGINE_PRECOMPILED_HEADER}
)

#
# Visual Studio Configuration
#

set_target_properties(
    Core
    PROPERTIES 
    FOLDER "Engine"
)
