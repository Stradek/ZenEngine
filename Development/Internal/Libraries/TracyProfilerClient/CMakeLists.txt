#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Files
#

set(TARGET_FILES
    "${TRACY_PUBLIC_DIRECTORY}/TracyClient.cpp"
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
    $<$<CONFIG:Debug>:${TRACY_PUBLIC_DIRECTORY}>
)