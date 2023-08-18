#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

set(SPDLOG_ROOT ${EXTERNAL_DIR}/spdlog)

#
# Include spdlog Library
#

add_subdirectory(${SPDLOG_ROOT} ${CMAKE_BINARY_DIR}/spdlog)

#
# Visual Studio Configuration
#

set_target_properties(
    spdlog
    PROPERTIES 
    FOLDER "Dependencies"
)
