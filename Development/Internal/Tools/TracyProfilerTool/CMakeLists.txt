#
# Copyright (c) 2023 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

include_guard(GLOBAL)

#
# Configuration
#

add_compile_definitions(
    _CRT_SECURE_NO_DEPRECATE
    _CRT_NONSTDC_NO_DEPRECATE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
    _USE_MATH_DEFINES
    IMGUI_ENABLE_FREETYPE
)

if(MSVC)
    # Enable Conformance mode
    set(TRACY_FLAGS "${TRACY_FLAGS} /permissive-")
    
    # Set Diagnostics Format to Caret
    set(TRACY_FLAGS "${TRACY_FLAGS} /diagnostics:caret")
    
    # Enable Advanced Vector Extensions 2
    set(TRACY_FLAGS "${TRACY_FLAGS} /arch:AVX2")
    
    # Disable Minimal Rebuild
    set(TRACY_FLAGS "${TRACY_FLAGS} /Gm-")
    
    # Enable Fast floating-point model
    set(TRACY_FLAGS "${TRACY_FLAGS} /fp:fast")
    
    # Enable Multi-Processor Compilation
    set(TRACY_FLAGS "${TRACY_FLAGS} /MP")
    
    # Set optimization to Disabled
    set(TRACY_FLAGS "${TRACY_FLAGS} /Od")
    
    # Enable Security Development Lifecycle checks
    set(TRACY_FLAGS "${TRACY_FLAGS} /sdl")
    
    # Set warning level to Level 3
    set(TRACY_FLAGS "${TRACY_FLAGS} /W3")

    add_compile_definitions("${TRACY_FLAGS}")
endif()



#
# Files
#

set(INCLUDE_DIRS 
    ${TRACY_ROOT}/imgui
    ${TRACY_DEPENDENCIES_HEADERS}
    ${TRACY_DEPENDENCIES_HEADERS}/capstone
)

set(SOURCE_FILES
    ${TRACY_ROOT}/imgui/imgui.cpp
    ${TRACY_ROOT}/imgui/imgui_demo.cpp
    ${TRACY_ROOT}/imgui/imgui_draw.cpp
    ${TRACY_ROOT}/imgui/imgui_tables.cpp
    ${TRACY_ROOT}/imgui/imgui_widgets.cpp
    ${TRACY_ROOT}/imgui/misc/freetype/imgui_freetype.cpp
    ${TRACY_ROOT}/nfd/nfd_win.cpp
    ${TRACY_ROOT}/public/common/TracySocket.cpp
    ${TRACY_ROOT}/public/common/TracyStackFrames.cpp
    ${TRACY_ROOT}/public/common/TracySystem.cpp
    ${TRACY_ROOT}/public/common/tracy_lz4.cpp
    ${TRACY_ROOT}/public/common/tracy_lz4hc.cpp
    ${TRACY_ROOT}/server/TracyBadVersion.cpp
    ${TRACY_ROOT}/server/TracyColor.cpp
    ${TRACY_ROOT}/server/TracyFileselector.cpp
    ${TRACY_ROOT}/server/TracyFilesystem.cpp
    ${TRACY_ROOT}/server/TracyImGui.cpp
    ${TRACY_ROOT}/server/TracyMemory.cpp
    ${TRACY_ROOT}/server/TracyMicroArchitecture.cpp
    ${TRACY_ROOT}/server/TracyMmap.cpp
    ${TRACY_ROOT}/server/TracyMouse.cpp
    ${TRACY_ROOT}/server/TracyPrint.cpp
    ${TRACY_ROOT}/server/TracyProtoHistory.cpp
    ${TRACY_ROOT}/server/TracySourceContents.cpp
    ${TRACY_ROOT}/server/TracySourceTokenizer.cpp
    ${TRACY_ROOT}/server/TracySourceView.cpp
    ${TRACY_ROOT}/server/TracyStorage.cpp
    ${TRACY_ROOT}/server/TracyTaskDispatch.cpp
    ${TRACY_ROOT}/server/TracyTexture.cpp
    ${TRACY_ROOT}/server/TracyTextureCompression.cpp
    ${TRACY_ROOT}/server/TracyThreadCompress.cpp
    ${TRACY_ROOT}/server/TracyTimelineController.cpp
    ${TRACY_ROOT}/server/TracyTimelineItem.cpp
    ${TRACY_ROOT}/server/TracyTimelineItemCpuData.cpp
    ${TRACY_ROOT}/server/TracyTimelineItemGpu.cpp
    ${TRACY_ROOT}/server/TracyTimelineItemPlot.cpp
    ${TRACY_ROOT}/server/TracyTimelineItemThread.cpp
    ${TRACY_ROOT}/server/TracyUserData.cpp
    ${TRACY_ROOT}/server/TracyUtility.cpp
    ${TRACY_ROOT}/server/TracyView.cpp
    ${TRACY_ROOT}/server/TracyView_Annotations.cpp
    ${TRACY_ROOT}/server/TracyView_Callstack.cpp
    ${TRACY_ROOT}/server/TracyView_Compare.cpp
    ${TRACY_ROOT}/server/TracyView_ConnectionState.cpp
    ${TRACY_ROOT}/server/TracyView_ContextSwitch.cpp
    ${TRACY_ROOT}/server/TracyView_CpuData.cpp
    ${TRACY_ROOT}/server/TracyView_FindZone.cpp
    ${TRACY_ROOT}/server/TracyView_FrameOverview.cpp
    ${TRACY_ROOT}/server/TracyView_FrameTimeline.cpp
    ${TRACY_ROOT}/server/TracyView_FrameTree.cpp
    ${TRACY_ROOT}/server/TracyView_GpuTimeline.cpp
    ${TRACY_ROOT}/server/TracyView_Locks.cpp
    ${TRACY_ROOT}/server/TracyView_Memory.cpp
    ${TRACY_ROOT}/server/TracyView_Messages.cpp
    ${TRACY_ROOT}/server/TracyView_Navigation.cpp
    ${TRACY_ROOT}/server/TracyView_NotificationArea.cpp
    ${TRACY_ROOT}/server/TracyView_Options.cpp
    ${TRACY_ROOT}/server/TracyView_Playback.cpp
    ${TRACY_ROOT}/server/TracyView_Plots.cpp
    ${TRACY_ROOT}/server/TracyView_Ranges.cpp
    ${TRACY_ROOT}/server/TracyView_Samples.cpp
    ${TRACY_ROOT}/server/TracyView_Statistics.cpp
    ${TRACY_ROOT}/server/TracyView_Timeline.cpp
    ${TRACY_ROOT}/server/TracyView_TraceInfo.cpp
    ${TRACY_ROOT}/server/TracyView_Utility.cpp
    ${TRACY_ROOT}/server/TracyView_ZoneInfo.cpp
    ${TRACY_ROOT}/server/TracyView_ZoneTimeline.cpp
    ${TRACY_ROOT}/server/TracyWeb.cpp
    ${TRACY_ROOT}/server/TracyWorker.cpp
    ${TRACY_ROOT}/zstd/common/debug.c
    ${TRACY_ROOT}/zstd/common/entropy_common.c
    ${TRACY_ROOT}/zstd/common/error_private.c
    ${TRACY_ROOT}/zstd/common/fse_decompress.c
    ${TRACY_ROOT}/zstd/common/pool.c
    ${TRACY_ROOT}/zstd/common/threading.c
    ${TRACY_ROOT}/zstd/common/xxhash.c
    ${TRACY_ROOT}/zstd/common/zstd_common.c
    ${TRACY_ROOT}/zstd/compress/fse_compress.c
    ${TRACY_ROOT}/zstd/compress/hist.c
    ${TRACY_ROOT}/zstd/compress/huf_compress.c
    ${TRACY_ROOT}/zstd/compress/zstdmt_compress.c
    ${TRACY_ROOT}/zstd/compress/zstd_compress.c
    ${TRACY_ROOT}/zstd/compress/zstd_compress_literals.c
    ${TRACY_ROOT}/zstd/compress/zstd_compress_sequences.c
    ${TRACY_ROOT}/zstd/compress/zstd_compress_superblock.c
    ${TRACY_ROOT}/zstd/compress/zstd_double_fast.c
    ${TRACY_ROOT}/zstd/compress/zstd_fast.c
    ${TRACY_ROOT}/zstd/compress/zstd_lazy.c
    ${TRACY_ROOT}/zstd/compress/zstd_ldm.c
    ${TRACY_ROOT}/zstd/compress/zstd_opt.c
    ${TRACY_ROOT}/zstd/decompress/huf_decompress.c
    ${TRACY_ROOT}/zstd/decompress/zstd_ddict.c
    ${TRACY_ROOT}/zstd/decompress/zstd_decompress.c
    ${TRACY_ROOT}/zstd/decompress/zstd_decompress_block.c
    ${TRACY_ROOT}/zstd/dictBuilder/cover.c
    ${TRACY_ROOT}/zstd/dictBuilder/divsufsort.c
    ${TRACY_ROOT}/zstd/dictBuilder/fastcover.c
    ${TRACY_ROOT}/zstd/dictBuilder/zdict.c
    ${TRACY_ROOT}/profiler/src/BackendGlfw.cpp
    ${TRACY_ROOT}/profiler/src/ConnectionHistory.cpp
    ${TRACY_ROOT}/profiler/src/Filters.cpp
    ${TRACY_ROOT}/profiler/src/Fonts.cpp
    ${TRACY_ROOT}/profiler/src/HttpRequest.cpp
    ${TRACY_ROOT}/profiler/src/ImGuiContext.cpp
    ${TRACY_ROOT}/profiler/src/imgui/imgui_impl_glfw.cpp
    ${TRACY_ROOT}/profiler/src/imgui/imgui_impl_opengl3.cpp
    ${TRACY_ROOT}/profiler/src/IsElevated.cpp
    ${TRACY_ROOT}/profiler/src/main.cpp
    ${TRACY_ROOT}/profiler/src/ResolvService.cpp
    ${TRACY_ROOT}/profiler/src/RunQueue.cpp
    ${TRACY_ROOT}/profiler/src/WindowPosition.cpp
    ${TRACY_ROOT}/profiler/src/winmain.cpp
    ${TRACY_ROOT}/profiler/src/winmainArchDiscovery.cpp
)

set(HEADER_FILES
    ${TRACY_ROOT}/imgui/imconfig.h
    ${TRACY_ROOT}/imgui/imgui.h
    ${TRACY_ROOT}/imgui/imgui_internal.h
    ${TRACY_ROOT}/imgui/imstb_rectpack.h
    ${TRACY_ROOT}/imgui/imstb_textedit.h
    ${TRACY_ROOT}/imgui/imstb_truetype.h
    ${TRACY_ROOT}/imgui/misc/freetype/imgui_freetype.h
    ${TRACY_ROOT}/nfd/nfd.h
    ${TRACY_ROOT}/public/common/TracyAlign.hpp
    ${TRACY_ROOT}/public/common/TracyAlloc.hpp
    ${TRACY_ROOT}/public/common/TracyApi.h
    ${TRACY_ROOT}/public/common/TracyColor.hpp
    ${TRACY_ROOT}/public/common/TracyForceInline.hpp
    ${TRACY_ROOT}/public/common/TracyMutex.hpp
    ${TRACY_ROOT}/public/common/TracyProtocol.hpp
    ${TRACY_ROOT}/public/common/TracyQueue.hpp
    ${TRACY_ROOT}/public/common/TracySocket.hpp
    ${TRACY_ROOT}/public/common/TracyStackFrames.hpp
    ${TRACY_ROOT}/public/common/TracySystem.hpp
    ${TRACY_ROOT}/public/common/TracyUwp.hpp
    ${TRACY_ROOT}/public/common/TracyVersion.hpp
    ${TRACY_ROOT}/public/common/TracyYield.hpp
    ${TRACY_ROOT}/public/common/tracy_lz4.hpp
    ${TRACY_ROOT}/public/common/tracy_lz4hc.hpp
    ${TRACY_ROOT}/server/IconsFontAwesome6.h
    ${TRACY_ROOT}/server/TracyBadVersion.hpp
    ${TRACY_ROOT}/server/TracyBuzzAnim.hpp
    ${TRACY_ROOT}/server/TracyCharUtil.hpp
    ${TRACY_ROOT}/server/TracyColor.hpp
    ${TRACY_ROOT}/server/TracyDecayValue.hpp
    ${TRACY_ROOT}/server/TracyEvent.hpp
    ${TRACY_ROOT}/server/TracyFileHeader.hpp
    ${TRACY_ROOT}/server/TracyFileRead.hpp
    ${TRACY_ROOT}/server/TracyFileselector.hpp
    ${TRACY_ROOT}/server/TracyFilesystem.hpp
    ${TRACY_ROOT}/server/TracyFileWrite.hpp
    ${TRACY_ROOT}/server/TracyImGui.hpp
    ${TRACY_ROOT}/server/TracyMemory.hpp
    ${TRACY_ROOT}/server/TracyMicroArchitecture.hpp
    ${TRACY_ROOT}/server/TracyMmap.hpp
    ${TRACY_ROOT}/server/TracyMouse.hpp
    ${TRACY_ROOT}/server/TracyPopcnt.hpp
    ${TRACY_ROOT}/server/TracyPrint.hpp
    ${TRACY_ROOT}/server/TracyProtoHistory.hpp
    ${TRACY_ROOT}/server/TracyShortPtr.hpp
    ${TRACY_ROOT}/server/TracySlab.hpp
    ${TRACY_ROOT}/server/TracySort.hpp
    ${TRACY_ROOT}/server/TracySortedVector.hpp
    ${TRACY_ROOT}/server/TracySourceContents.hpp
    ${TRACY_ROOT}/server/TracySourceTokenizer.hpp
    ${TRACY_ROOT}/server/TracySourceView.hpp
    ${TRACY_ROOT}/server/TracyStorage.hpp
    ${TRACY_ROOT}/server/TracyStringDiscovery.hpp
    ${TRACY_ROOT}/server/TracyTaskDispatch.hpp
    ${TRACY_ROOT}/server/TracyTexture.hpp
    ${TRACY_ROOT}/server/TracyTextureCompression.hpp
    ${TRACY_ROOT}/server/TracyThreadCompress.hpp
    ${TRACY_ROOT}/server/TracyTimelineController.hpp
    ${TRACY_ROOT}/server/TracyTimelineItem.hpp
    ${TRACY_ROOT}/server/TracyTimelineItemCpuData.hpp
    ${TRACY_ROOT}/server/TracyTimelineItemGpu.hpp
    ${TRACY_ROOT}/server/TracyTimelineItemPlot.hpp
    ${TRACY_ROOT}/server/TracyTimelineItemThread.hpp
    ${TRACY_ROOT}/server/TracyUserData.hpp
    ${TRACY_ROOT}/server/TracyUtility.hpp
    ${TRACY_ROOT}/server/TracyVarArray.hpp
    ${TRACY_ROOT}/server/TracyVector.hpp
    ${TRACY_ROOT}/server/TracyView.hpp
    ${TRACY_ROOT}/server/TracyViewData.hpp
    ${TRACY_ROOT}/server/TracyWeb.hpp
    ${TRACY_ROOT}/server/TracyWorker.hpp
    ${TRACY_ROOT}/server/tracy_pdqsort.h
    ${TRACY_ROOT}/server/tracy_robin_hood.h
    ${TRACY_ROOT}/server/tracy_xxhash.h
    ${TRACY_ROOT}/zstd/common/bitstream.h
    ${TRACY_ROOT}/zstd/common/compiler.h
    ${TRACY_ROOT}/zstd/common/cpu.h
    ${TRACY_ROOT}/zstd/common/debug.h
    ${TRACY_ROOT}/zstd/common/error_private.h
    ${TRACY_ROOT}/zstd/common/fse.h
    ${TRACY_ROOT}/zstd/common/huf.h
    ${TRACY_ROOT}/zstd/common/mem.h
    ${TRACY_ROOT}/zstd/common/pool.h
    ${TRACY_ROOT}/zstd/common/portability_macros.h
    ${TRACY_ROOT}/zstd/common/threading.h
    ${TRACY_ROOT}/zstd/common/xxhash.h
    ${TRACY_ROOT}/zstd/common/zstd_deps.h
    ${TRACY_ROOT}/zstd/common/zstd_internal.h
    ${TRACY_ROOT}/zstd/common/zstd_trace.h
    ${TRACY_ROOT}/zstd/compress/clevels.h
    ${TRACY_ROOT}/zstd/compress/hist.h
    ${TRACY_ROOT}/zstd/compress/zstdmt_compress.h
    ${TRACY_ROOT}/zstd/compress/zstd_compress_internal.h
    ${TRACY_ROOT}/zstd/compress/zstd_compress_literals.h
    ${TRACY_ROOT}/zstd/compress/zstd_compress_sequences.h
    ${TRACY_ROOT}/zstd/compress/zstd_compress_superblock.h
    ${TRACY_ROOT}/zstd/compress/zstd_cwksp.h
    ${TRACY_ROOT}/zstd/compress/zstd_double_fast.h
    ${TRACY_ROOT}/zstd/compress/zstd_fast.h
    ${TRACY_ROOT}/zstd/compress/zstd_lazy.h
    ${TRACY_ROOT}/zstd/compress/zstd_ldm.h
    ${TRACY_ROOT}/zstd/compress/zstd_ldm_geartab.h
    ${TRACY_ROOT}/zstd/compress/zstd_opt.h
    ${TRACY_ROOT}/zstd/decompress/zstd_ddict.h
    ${TRACY_ROOT}/zstd/decompress/zstd_decompress_block.h
    ${TRACY_ROOT}/zstd/decompress/zstd_decompress_internal.h
    ${TRACY_ROOT}/zstd/dictBuilder/cover.h
    ${TRACY_ROOT}/zstd/dictBuilder/divsufsort.h
    ${TRACY_ROOT}/zstd/zdict.h
    ${TRACY_ROOT}/zstd/zstd.h
    ${TRACY_ROOT}/zstd/zstd_errors.h
    ${TRACY_ROOT}/profiler/src/Backend.hpp
    ${TRACY_ROOT}/profiler/src/ConnectionHistory.hpp
    ${TRACY_ROOT}/profiler/src/Filters.hpp
    ${TRACY_ROOT}/profiler/src/Fonts.hpp
    ${TRACY_ROOT}/profiler/src/font/DroidSans.hpp
    ${TRACY_ROOT}/profiler/src/font/FiraCodeRetina.hpp
    ${TRACY_ROOT}/profiler/src/font/FontAwesomeSolid.hpp
    ${TRACY_ROOT}/profiler/src/HttpRequest.hpp
    ${TRACY_ROOT}/profiler/src/icon.hpp
    ${TRACY_ROOT}/profiler/src/ImGuiContext.hpp
    ${TRACY_ROOT}/profiler/src/imgui/imgui_impl_glfw.h
    ${TRACY_ROOT}/profiler/src/imgui/imgui_impl_opengl3.h
    ${TRACY_ROOT}/profiler/src/imgui/imgui_impl_opengl3_loader.h
    ${TRACY_ROOT}/profiler/src/IsElevated.hpp
    ${TRACY_ROOT}/profiler/src/ResolvService.hpp
    ${TRACY_ROOT}/profiler/src/RunQueue.hpp
    ${TRACY_ROOT}/profiler/src/stb_image.h
    ${TRACY_ROOT}/profiler/src/WindowPosition.hpp
)

set(TARGET_FILES
    "${SOURCE_FILES}"
    "${HEADER_FILES}"
)

#
# Executable
#

add_executable(TracyProfilerTool WIN32
    "${TARGET_FILES}"
)

link_directories(
    ${TRACY_DEPENDENCIES_ROOT}/debug/lib
)

target_link_libraries(TracyProfilerTool PRIVATE
    brotlicommon-static brotlidec-static ws2_32 brotlienc-static bz2d capstone freetyped glfw3 libpng16d zlibd
)

target_include_directories(TracyProfilerTool PRIVATE
    "${INCLUDE_DIRS}"
)

#
# Linker Configuration
#

set_target_properties(TracyProfilerTool 
    PROPERTIES 
    LINKER_LANGUAGE CXX
)
