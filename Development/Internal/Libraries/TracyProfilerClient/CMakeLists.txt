#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Files
#

set(SOURCE_FILES
    "${TRACY_ROOT}/public/TracyClient.cpp"
)

set(TARGET_FILES
    "${SOURCE_FILES}"
)

#
# Library
#

add_library(TracyProfilerClient STATIC
    "${TARGET_FILES}"
)

target_compile_definitions(TracyProfilerClient PUBLIC
    "$<$<CONFIG:Debug>:TRACY_ENABLE; TRACY_ONLY_LOCALHOST>"
)

# include Tracy headers only for targets
# that are linked agains TracyProfilerClient
target_include_directories(TracyProfilerClient INTERFACE
    $<$<CONFIG:Debug>:${TRACY_HEADER_DIR}>
)