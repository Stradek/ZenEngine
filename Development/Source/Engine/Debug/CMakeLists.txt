#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Files
#

set(INCLUDE_DIR ${ENGINE_INTERNAL_INCLUDE_DIR}/Debug)

get_all_target_files(TARGET_FILES 0 ${INCLUDE_DIR})

#
# Library
#

add_library(Debug STATIC
    "${TARGET_FILES}"
)

target_include_directories(Debug PRIVATE
    ${INCLUDE_DIR}
)

#
# Internal Dependencies
#

target_link_libraries(Debug PUBLIC 
    # Engine
    Core
)

#
# Visual Studio Configuration
#

set_target_properties(
    Debug
    PROPERTIES 
    FOLDER "Engine"
)