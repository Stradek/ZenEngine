#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(RENDERER_INCLUDE_DIR ${ENGINE_INCLUDE_DIR}/Renderer)

set(RENDERER_INCLUDE_DIR ${RENDERER_INCLUDE_DIR} PARENT_SCOPE)

get_source_files(RENDERER_SOURCE_FILES 0 ${SOURCE_DIR})
get_header_files(RENDERER_HEADER_FILES 0 ${RENDERER_INCLUDE_DIR})

set(RENDERER_FILES 
    "${RENDERER_SOURCE_FILES}"
    "${RENDERER_HEADER_FILES}"
)

#
# Library
#

add_library(Renderer
    STATIC
    "${RENDERER_FILES}"
)

set_property(TARGET Renderer PROPERTY FOLDER "Engine")
target_include_directories(Renderer PRIVATE
    ${RENDERER_INCLUDE_DIR}
        
    # Dependencies
    ${ENGINE_INCLUDE_DIR}
)

#
# Dependencies
#

# Engine dependencies
target_link_libraries(Renderer PRIVATE Core Debug)

set(SDL_TEST                OFF
    SDL2_DISABLE_SDL2MAIN   ON
    SDL2_DISABLE_INSTALL    ON
    SDL2_DISABLE_UNINSTALL  ON
    SDL_SHARED              ON
    SDL_STATIC              OFF
)

# SDL library
add_subdirectory(${SDL_ROOT} ${CMAKE_BINARY_DIR}/SDL)

set_target_properties(
    SDL2 SDL2main sdl-build-options SDL2-static SDL2_test sdl_headers_copy uninstall PROPERTIES FOLDER "Dependencies/SDL2")

target_link_libraries(Renderer PUBLIC SDL2)
target_include_directories(Renderer PRIVATE
    ${SDL_ROOT}/include
)

# 
# Precompiled Headers
#

target_precompile_headers(Renderer
    PRIVATE
    ${ENGINE_PRECOMILED_HEADER}
)