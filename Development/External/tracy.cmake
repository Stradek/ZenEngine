#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

set(TRACY_ROOT ${EXTERNAL_DIR}/tracy)
set(TRACY_HEADER_DIR ${TRACY_ROOT}/public)
set(TRACY_DEPENDENCIES_ROOT ${EXTERNAL_DIR}/tracy_dependencies)
set(TRACY_DEPENDENCIES_HEADERS ${TRACY_DEPENDENCIES_ROOT}/include)