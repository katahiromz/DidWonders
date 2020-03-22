# CMakeLists.txt --- CMake project settings
#    ex) cmake -G "Visual Studio 9 2008" .
#    ex) cmake -DCMAKE_BUILD_TYPE=Release -G "MSYS Makefiles" .
##############################################################################

# CMake minimum version
cmake_minimum_required(VERSION 2.4)

# project name and languages
project(DidWonders C CXX RC)

# set output directory (build/)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# enable Win32 resource
enable_language(RC)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # using Clang
    set(CMAKE_C_FLAGS "-static")
    set(CMAKE_CXX_FLAGS "-static")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # using GCC
    set(CMAKE_C_FLAGS "-static")
    set(CMAKE_CXX_FLAGS "-static")
elseif (MSVC)
    # replace "/MD" with "/MT" (building without runtime DLLs)
    set(CompilerFlags
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    foreach(CompilerFlags ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlags} "${${CompilerFlags}}")
    endforeach()
endif()

##############################################################################

include_directories(TypeSystem)

subdirs(TypeSystem tools)

file(GENERATE OUTPUT ${PROJECT_SOURCE_DIR}/config_$<CONFIG>.bat CONTENT
"@echo off
set REDIRECTOR=$<TARGET_FILE:redirector>
set IWON=$<TARGET_FILE:iwon>
set MCPP=${PROJECT_SOURCE_DIR}/tools/mcpp/mcpp.exe
set CPARSER=$<TARGET_FILE:cparser>
set DLLEXPDUMPER=$<TARGET_FILE:dllexpdumper>
")

if(MSVC)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        add_custom_target(do-wonders ALL
                          COMMAND ${PROJECT_SOURCE_DIR}/do-wonders-cl-64.bat
                          DEPENDS redirector mcpp cparser dllexpdumper)
    else()
        add_custom_target(do-wonders ALL
                          COMMAND ${PROJECT_SOURCE_DIR}/do-wonders-cl-32.bat
                          DEPENDS redirector mcpp cparser dllexpdumper)
    endif()
endif()

##############################################################################
