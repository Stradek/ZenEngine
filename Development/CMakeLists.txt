#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Targets Configuration
#

set(MAIN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Include)
set(MAIN_ENGINE_INCLUDE_DIR ${MAIN_INCLUDE_DIR}/Engine)

set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/External)

set(SPDLOG_ROOT ${EXTERNAL_DIR}/spdlog)
set(FMT_ROOT ${EXTERNAL_DIR}/fmt)

#
# Sources
#

add_subdirectory(Source)