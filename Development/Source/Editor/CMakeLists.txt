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
# Executable
#

add_executable(Editor
    "${TARGET_FILES}"
)

target_include_directories(Editor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

#
# Internal Dependencies
#

target_link_libraries(Editor PRIVATE 
    Engine
)

#
# Post Build
#

add_custom_command(TARGET Editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${SDL_DLL} $<TARGET_FILE_DIR:Editor>
)

#
# Visual Studio Configuration
#

set_target_properties(
    Editor
    PROPERTIES 
    FOLDER "Editor"
)