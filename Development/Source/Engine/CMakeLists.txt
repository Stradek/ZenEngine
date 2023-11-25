#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

#
# Files
#

set(ENGINE_PRECOMPILED_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h")
set(ENGINE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

get_all_target_files(TARGET_FILES 0 ${CMAKE_CURRENT_SOURCE_DIR})

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

target_include_directories(Engine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Engine PUBLIC 
    # Engine
    Common Core Debug WindowManagement Graphics EventSystem

    # Internal 
    $<$<CONFIG:Debug>:TracyProfilerClient>
)

# definition to aviod SDL preprocessor rule to 
# redefine main() as SDL_main()
target_compile_definitions(Engine PUBLIC
    "SDL_MAIN_HANDLED"
)

#
# Visual Studio Configuration
#

set_target_properties(Engine
    PROPERTIES 
    FOLDER "Engine"
)