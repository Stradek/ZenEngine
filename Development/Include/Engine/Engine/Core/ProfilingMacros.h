/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

 // IMPORTANT: This header should be included in both Debug and Release configuration
 // The macros defined here do have their non-functional counterpart 
 // for non-Debug configurations

#ifdef _DEBUG

#include <tracy/Tracy.hpp>

#define ENGINE_INCREMENT_COUNTER(name) {																\
	ENGINE_WARN("ENGINE_INCREMENT_COUNTER not implemented.");											\
}

#define ENGINE_FRAME_MARK_START(name) {																	\
	ENGINE_WARN("ENGINE_FRAME_MARK_START is not calling Frame Profiling Start.");						\
	FrameMarkStart(name);																				\
}

#define ENGINE_FRAME_MARK_END(name) {																	\
	ENGINE_WARN("ENGINE_FRAME_MARK_START is not calling Frame Profiling End.");							\
	FrameMarkEnd(name);																					\
	ENGINE_INCREMENT_COUNTER(name);																		\
}

#define ENGINE_FRAME_MARK() {																			\
	FrameMark;																							\
}

#else

#define ENGINE_INCREMENT_COUNTER(x)
#define ENGINE_FRAME_MARK_START(x)
#define ENGINE_FRAME_MARK_END(x)
#define ENGINE_FRAME_MARK()

#endif