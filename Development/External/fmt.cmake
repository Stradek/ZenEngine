#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

set(FMT_ROOT ${EXTERNAL_DIR}/fmt-10.0.0)

#
# Libraries
#

set(FMT_LIB 
    $<$<CONFIG:Debug>:${FMT_ROOT}/lib/x64/Debug/fmtd.lib>
    $<$<CONFIG:Release>:${FMT_ROOT}/lib/x64/Release/fmt.lib>
)

#
# Include Directory
#

set(FMT_INCLUDE_DIR ${FMT_ROOT}/include)