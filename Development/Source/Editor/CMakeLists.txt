#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(EDITOR_INCLUDE_DIR ${MAIN_INCLUDE_DIR}/Editor)

set(EDITOR_INCLUDE_DIR ${EDITOR_INCLUDE_DIR} PARENT_SCOPE)

get_source_files(EDITOR_SOURCE_FILES 0 ${SOURCE_DIR})
get_header_files(EDITOR_HEADER_FILES 0 ${EDITOR_INCLUDE_DIR})

set(EDITOR_FILES 
    "${EDITOR_SOURCE_FILES}"
    "${EDITOR_SOURCE_FILES}"
)

#
# Executable
#

add_executable(Editor
    "${EDITOR_FILES}"
)

set_property(TARGET Editor PROPERTY FOLDER "Editor")
target_include_directories(Editor PUBLIC
    ${EDITOR_INCLUDE_DIR}
)

#
# Dependencies
#

# Engine dependency
target_link_libraries(Editor PUBLIC Engine)
target_include_directories(Editor PUBLIC
     ${MAIN_ENGINE_INCLUDE_DIR}
)

# Tracy dependency
target_link_libraries(Editor PUBLIC TracyProfilerClient)