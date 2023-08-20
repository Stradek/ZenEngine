#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

add_compile_definitions(
    "$<$<CONFIG:Debug>:TRACY_ENABLE; TRACY_ONLY_LOCALHOST>"
)

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
