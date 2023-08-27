#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

set(SDL_ROOT ${EXTERNAL_DIR}/SDL2-2.28.0)

#
# Libraries
#

set(SDL_LIB 
    $<$<CONFIG:Debug>:${SDL_ROOT}/lib/x64/Debug/SDL2d.lib>
    $<$<CONFIG:Release>:${SDL_ROOT}/lib/x64/Release/SDL2.lib>
)

set(SDL_DLL 
    $<$<CONFIG:Debug>:${SDL_ROOT}/lib/x64/Debug/SDL2d.dll>
    $<$<CONFIG:Release>:${SDL_ROOT}/lib/x64/Release/SDL2.dll>
)

#
# Include Directory
#

set(SDL_INCLUDE_DIR ${SDL_ROOT}/include)