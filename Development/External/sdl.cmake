#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

set(SDL_ROOT ${EXTERNAL_DIR}/SDL)

set(SDL_TEST                OFF
    SDL2_DISABLE_SDL2MAIN   ON
    SDL2_DISABLE_INSTALL    ON
    SDL2_DISABLE_UNINSTALL  ON
    SDL_SHARED              ON
    SDL_STATIC              OFF
)

#
# Include Library
#

add_subdirectory(${SDL_ROOT} ${CMAKE_BINARY_DIR}/SDL)

#
# Visual Studio Configuration
#

set_target_properties(
    SDL2 SDL2main sdl-build-options SDL2-static 
    SDL2_test sdl_headers_copy uninstall 
    PROPERTIES 
    FOLDER "Dependencies/External/SDL2"
)