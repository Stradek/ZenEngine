#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

add_compile_definitions(
    "$<$<CONFIG:Debug>:TRACY_ENABLE; TRACY_ONLY_LOCALHOST>"
)

#
# Sources
#

set(TRACY_PROFILER_CLIENT_FILES
    "${TRACY_ROOT}/public/TracyClient.cpp"
)

#
# Library
#

add_library(TracyProfilerClient
    STATIC
    "${TRACY_PROFILER_CLIENT_FILES}"
)

set_property(TARGET TracyProfilerClient PROPERTY FOLDER "Dependencies")