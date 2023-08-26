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
	GameEngine::getInstance()->GetDebugManager()->GetPerformanceProfiler()->IncrementCounter(name, 1);	\
}

#define ENGINE_FRAME_MARK_START(name) {																	\
	GameEngine::getInstance()->GetDebugManager()->GetPerformanceProfiler()->FrameProfilingStart(name);	\
	FrameMarkStart(name);																				\
}

#define ENGINE_FRAME_MARK_END(name) {																	\
	GameEngine::getInstance()->GetDebugManager()->GetPerformanceProfiler()->FrameProfilingEnd(name);	\
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