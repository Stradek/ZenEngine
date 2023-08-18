#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

set(INCLUDE_DIR ${MAIN_INCLUDE_DIR}/Engine)

# This one is needed for Core subsystem to link it to every other subsystem
# then every linked project include in engine systems needs start with <Engine/...>
set(ENGINE_INCLUDE_DIR_CORE ${INCLUDE_DIR})

set(ENGINE_INTERNAL_INCLUDE_DIR ${INCLUDE_DIR}/Engine)


# Tracy dependency
add_compile_definitions(
    "$<$<CONFIG:Debug>:TRACY_ENABLE>"
)

#
# Library
#

get_all_target_files(TARGET_FILES 0 ${ENGINE_INTERNAL_INCLUDE_DIR})

add_library(Engine
    STATIC
    "${TARGET_FILES}"
)

target_include_directories(Engine PUBLIC
    ${INCLUDE_DIR}
)

#
# Dependencies
#

add_subdirectory("Common")
add_subdirectory("Core")
add_subdirectory("Debug")
add_subdirectory("Graphics")
add_subdirectory("EventSystem")

target_link_libraries(Engine PUBLIC 
    # Engine
    Common Core Debug Graphics EventSystem

    # Internal 
    TracyProfilerClient
)

#
# Precompiled Headers
#

target_precompile_headers(Engine
    PUBLIC
    ${ENGINE_PRECOMILED_HEADER}
)

#
# Visual Studio Configuration
#

set_target_properties(
    Engine
    PROPERTIES 
    FOLDER "Engine"
)