cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
set(PRJ_NAME AyonCppLogger)
project(AyonCppLogger VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/bin)


set(AYONCPPLOGGERLIBTYPE STATIC)
if (DEFINED ENV{AYONCPPLOGGERLIBTYPE})
  message("Shared Build")
  set(AYONCPPLOGGERLIBTYPE SHARED)
  set(BUILD_SHARED_LIBS ON)
endif()

set(Build_Test $ENV{BUILDTEST})
set(BUILD_TEST FALSE)
if (DEFINED ENV{BUILDTEST})
    message("Build Test ACTIVATED")
    set(BUILD_TEST TRUE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


option(BUILD_TEST "Build the test application" OFF)


add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ext/spdlog" EXCLUDE_FROM_ALL)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/ext/spdlog/include")

include("${CMAKE_CURRENT_SOURCE_DIR}/ext/AyonCppDevTools/CMakeInclude.txt")


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/AyonCppLogger")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/AyonCppLogger")


add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
