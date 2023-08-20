#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

set(FMT_ROOT ${EXTERNAL_DIR}/fmt)

#
# Include Library
#

add_subdirectory(${FMT_ROOT} ${CMAKE_BINARY_DIR}/fmt)

#
# Visual Studio Configuration
#

set_target_properties(
    fmt 
    PROPERTIES 
    FOLDER "Dependencies/External"
)
