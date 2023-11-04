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
	GameEngine::GetInstance().GetDebugManager().GetPerformanceProfiler().IncreaseCounter(name);			\
}

#define ENGINE_FRAME_MARK_START(name) {																	\
	FrameMarkStart(name);																				\
	GameEngine::GetInstance().GetDebugManager().GetPerformanceProfiler().AddFrameStart(name);			\
}

#define ENGINE_FRAME_MARK_END(name) {																	\
	FrameMarkEnd(name);																					\
	GameEngine::GetInstance().GetDebugManager().GetPerformanceProfiler().AddFrameEnd(name);				\
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