function(custom_cmake_setup)
    # Prevent this function from running more than once.
    if(CUSTOM_CMAKE_SETUP_CALLED)
        return()
    endif()

    set(CUSTOM_CMAKE_SETUP_CALLED TRUE PARENT_SCOPE)

    #
    # Options
    #

    # !!!Important Note!!!
    # 
    # Do not use (/ZI) as it is needed to be disabled for Tracy support 

    # Specify required C++ standard version.
    set(CMAKE_CXX_STANDARD 17 PARENT_SCOPE)
    set(CMAKE_CXX_STANDARD_REQUIRED ON PARENT_SCOPE)
    
    # Enable fast math.
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:fast" PARENT_SCOPE)
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math" PARENT_SCOPE)
    endif()

    # Enable intrinsic functions in Release configuration.
    if(MSVC)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi" PARENT_SCOPE)
    else()
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fipa-pta" PARENT_SCOPE)
    endif()

    # Enable whole program optimization in Release configuration.
    if(MSVC)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2" PARENT_SCOPE)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL" PARENT_SCOPE)
        set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} /LTCG")
        set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /LTCG")
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
    else()
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3" PARENT_SCOPE)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto" PARENT_SCOPE)
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto" PARENT_SCOPE)
        set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} -flto" PARENT_SCOPE)
    endif()

    # Enable warnings and debug info for Debug configuration
    if(MSVC)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4" PARENT_SCOPE)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi" PARENT_SCOPE)
    else()
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra" PARENT_SCOPE)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g" PARENT_SCOPE)
    endif()

    # Multithreaded compilation and faster PDB generation in parallel builds
    if(MSVC)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zf /MP" PARENT_SCOPE)
    endif()

    # Mark as GUI application on Release (leave commandline on Debug)
    if (MSVC)
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE  "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" PARENT_SCOPE)
    else()
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mwindows" PARENT_SCOPE)
    endif()
    
    #
    # Configurations
    #

    # Define custom set of configurations.
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

    # Set defines for identifying each configuration from code
    add_compile_definitions(
        "$<$<CONFIG:Debug>:CMAKE_CONFIG_DEBUG>"
        "$<$<CONFIG:Release>:CMAKE_CONFIG_RELEASE>"
    )

    #
    # Environment
    #

    # Enable folders feature in generated Visual Studio solution.
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    #
    # Project Helper functions
    #

    set(SOURCE_FILE_TYPES 
        "*.cpp"
        "*.hpp"
        "*.h"
        PARENT_SCOPE
    )

    set(HEADER_FILE_TYPES 
        "*.hpp" 
        "*.h"
        PARENT_SCOPE
    )

    # Search files in given directory with given filetype
    function(get_files_for_file_type RESULT_VAR USE_RECURSE FILES_DIR FILE_TYPES)
        #message(STATUS "get_files_for_file_type")
        #message(STATUS "DIR: ${FILES_DIR}")
        #message(STATUS "FILETYPES: ${FILE_TYPES}")
        set(MATCHING_FILES "")
        foreach(FILE_TYPE IN LISTS FILE_TYPES)
            if(USE_RECURSE)
                file(GLOB_RECURSE FILES
                    ${FILES_DIR}/${FILE_TYPE}
                )
            else()
                file(GLOB FILES
                    ${FILES_DIR}/${FILE_TYPE}
                )
            endif()
            list(LENGTH FILES listlen)
            if(listlen GREATER 0)
                list(APPEND MATCHING_FILES "${FILES}")
            endif()
        endforeach()

        set(${RESULT_VAR} "${MATCHING_FILES}" PARENT_SCOPE)
    endfunction()

    # Search source files in given directory
    function(get_source_files RESULT_VAR USE_RECURSE SOURCE_DIR)
        #message(STATUS "get_source_files")
        #message(STATUS "FILETYPES: ${SOURCE_FILE_TYPES}")

        get_files_for_file_type(SOURCE_FILES ${USE_RECURSE} "${SOURCE_DIR}" "${SOURCE_FILE_TYPES}")

        #message(STATUS "SOURCE: ${SOURCE_FILES}")

        set(${RESULT_VAR} "${SOURCE_FILES}" PARENT_SCOPE)
    endfunction()

    # Search header files in given directory
    function(get_header_files RESULT_VAR USE_RECURSE INCLUDE_DIR)
        #message(STATUS "get_header_files")
        #message(STATUS "FILETYPES: ${HEADER_FILE_TYPES}")

        get_files_for_file_type(HEADER_FILES ${USE_RECURSE} "${INCLUDE_DIR}" "${HEADER_FILE_TYPES}")

        #message(STATUS "HEADERS: ${HEADER_FILES}")

        set(${RESULT_VAR} "${HEADER_FILES}" PARENT_SCOPE)
    endfunction()

    # Search source and header files in given directory
    function(get_all_target_files RESULT_VAR USE_RECURSE DIRECTORY)
        get_source_files(TARGET_SOURCE_FILES ${USE_RECURSE} "${DIRECTORY}")
        get_header_files(TARGET_HEADER_FILES ${USE_RECURSE} "${DIRECTORY}")
        set(${RESULT_VAR} 
            "${TARGET_SOURCE_FILES}"
            "${TARGET_HEADER_FILES}"
            PARENT_SCOPE
        )
    endfunction()
endfunction()