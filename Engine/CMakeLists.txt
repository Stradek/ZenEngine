#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Sources
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source/Private)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source/Public)

set(FILE_HEADERS
    ${INCLUDE_DIR}/*.hpp
    ${INCLUDE_DIR}/*.h
)

set(FILE_SOURCES
    ${SOURCE_DIR}/*.cpp
    ${SOURCE_DIR}/*.hpp
    ${SOURCE_DIR}/*.h
)

file(GLOB_RECURSE FILES_HEADERS_ENGINE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${FILE_HEADERS}
)

file(GLOB_RECURSE FILES_SOURCES_ENGINE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${FILE_SOURCES}
)

#
# Library
#

add_library(Engine
    STATIC
    ${FILES_SOURCES_ENGINE}
)

set_property(TARGET Engine PROPERTY FOLDER "Engine")
target_include_directories(Engine PUBLIC
    ${FILES_HEADERS_ENGINE}
)

#
# Dependencies
#

# Example: 
# add_subdirectory("Engine", "../Engine/Core")
# target_link_libraries(Engine PUBLIC Core)

#
# Finish Settings
#

# Change working directory to top dir to access assets folder
set_property(TARGET Engine PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/..)
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Engine)