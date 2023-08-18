#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

set(INCLUDE_DIR ${MAIN_INCLUDE_DIR}/Editor)

#
# Executable
#

get_all_target_files(TARGET_FILES 0 ${INCLUDE_DIR})

add_executable(Editor
    "${TARGET_FILES}"
)

target_include_directories(Editor PUBLIC
    ${EDITOR_INCLUDE_DIR}
)

#
# Dependencies
#

# Engine dependency
target_link_libraries(Editor PUBLIC Engine)

#
# Visual Studio Configuration
#

set_target_properties(
    Editor
    PROPERTIES 
    FOLDER "Editor"
)