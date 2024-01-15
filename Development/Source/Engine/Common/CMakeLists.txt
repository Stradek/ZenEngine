#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Files
#

get_all_target_files(TARGET_FILES 1 ${CMAKE_CURRENT_SOURCE_DIR})

#
# Library
#

add_library(Common STATIC
    "${TARGET_FILES}"
)

target_include_directories(Common PUBLIC
    ${ENGINE_SOURCE_DIR}
)

#
# Visual Studio Configuration
#

set_target_properties(Common
    PROPERTIES 
    FOLDER "Engine"
)