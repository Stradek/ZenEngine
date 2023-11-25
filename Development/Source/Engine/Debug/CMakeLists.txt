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
# Library
#

add_library(Debug STATIC
    "${TARGET_FILES}"
)

target_include_directories(Debug PRIVATE
    ${ENGINE_SOURCE_DIR}
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