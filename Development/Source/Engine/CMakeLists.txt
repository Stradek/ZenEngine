#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

# Tracy dependency
add_compile_definitions(
    "$<$<CONFIG:Debug>:TRACY_ENABLE>"
)

#
# Files
#

set(INCLUDE_DIR
    ${MAIN_INCLUDE_DIR}/Engine
)

# This one is needed for Core subsystem to link it to every other subsystem
# then every linked project include in engine systems needs start with <Engine/...>
set(ENGINE_INCLUDE_DIR_CORE ${INCLUDE_DIR})

set(ENGINE_INTERNAL_INCLUDE_DIR ${INCLUDE_DIR}/Engine)

get_all_target_files(TARGET_FILES 0 ${ENGINE_INTERNAL_INCLUDE_DIR})

#
# Include Dependencies
#

add_subdirectory("Common")
add_subdirectory("Core")
add_subdirectory("Debug")
add_subdirectory("WindowManagement")
add_subdirectory("Graphics")
add_subdirectory("EventSystem")

#
# Library
#

add_library(Engine STATIC
    "${TARGET_FILES}"
)

target_include_directories(Engine PUBLIC
    ${INCLUDE_DIR}

    # Tracy dependency
    $<$<CONFIG:Debug>:${TRACY_HEADER_DIR}>
)

target_link_libraries(Engine PUBLIC 
    # Engine
    Common Core Debug WindowManagement Graphics EventSystem

    # Internal 
    $<$<CONFIG:Debug>:TracyProfilerClient>
)

#
# Visual Studio Configuration
#

set_target_properties(Engine
    PROPERTIES 
    FOLDER "Engine"
)