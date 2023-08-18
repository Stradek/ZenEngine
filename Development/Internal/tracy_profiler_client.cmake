#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

add_subdirectory(${INTERNAL_DIR}/Libraries/TracyProfilerClient)

#
# Visual Studio Configuration
#

set_target_properties(
    TracyProfilerClient 
    PROPERTIES 
    FOLDER "Dependencies/Internal"
)