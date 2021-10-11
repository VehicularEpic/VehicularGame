cmake_minimum_required(VERSION 3.15)
project(VehicularEpic)

# C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CONFIGURATION_TYPES Debug Release)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif ()

# Use folders in the resulting project files.
set_property(GLOBAL PROPERTY OS_FOLDERS ON)

set(GLAD_API gl:core=3.3)
set(CEF_VERSION "94.4.5+g0fd0d6f+chromium-94.0.4606.71")

set(PROJECT_EXTERNAL_MODULES ${CMAKE_SOURCE_DIR}/modules)

find_package(GLAD)
find_package(GLFW)

find_package(CEF)
SET_CEF_TARGET_OUT_DIR()

file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp src/*.hpp)
source_group(${CMAKE_PROJECT_NAME} FILES ${PROJECT_SOURCES})

set(LINKED_LIBS glad glfw libcef_lib libcef_dll_wrapper)

add_compile_definitions("$<$<CONFIG:Debug>:DEBUG_ENVIRONMENT>")
add_compile_definitions("$<$<CONFIG:Release>:RELEASE_ENVIRONMENT>")

include(platform/linux)
include(platform/windows)

# Copy binary and resource files to the target output directory.
COPY_FILES("${CMAKE_PROJECT_NAME}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
COPY_FILES("${CMAKE_PROJECT_NAME}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")

# Copy game assets folder
COPY_FILES("${CMAKE_PROJECT_NAME}" "assets" "${CMAKE_SOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")
