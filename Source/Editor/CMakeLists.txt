#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Include/Editor)

get_source_files(EDITOR_SOURCE_FILES 0 ${SOURCE_DIR})
get_header_files(EDITOR_HEADER_FILES 1 ${INCLUDE_DIR})

#
# Executable
#

add_executable(Editor
    "${EDITOR_SOURCE_FILES}"
    "${EDITOR_HEADER_FILES}"
)

set_property(TARGET Editor PROPERTY FOLDER "Editor")
target_include_directories(Editor PUBLIC
    "${PROJECT_SOURCE_DIR}/Include"
    "${PROJECT_SOURCE_DIR}/Source/Editor"
    "${PROJECT_SOURCE_DIR}/Source/Engine"
)

#
# Dependencies
#

# Example: 
# add_subdirectory("Engine")
# target_link_libraries(Engine PUBLIC Core)
# target_include_directories(Editor PUBLIC
#     ${FILES_HEADERS_EDITOR}
# )

#
# Finish Settings
#

# Change working directory to top dir to access assets folder
set_property(TARGET Editor PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})