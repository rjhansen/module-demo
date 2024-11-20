# CMake 3.30 is required for C++20 "import std" support. 
cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

# This magic must be invoked BEFORE the call to project().
#
# "import std" is still an experimental CMake feature and as such
# has to be added via a magic GUID.  This may change in the future.
# I found it in CMake source code under "Help/dev/experimental.rst",
# so look there if this script suddenly breaks.
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
    "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_STANDARD 23 REQUIRED)
set(CMAKE_CXX_MODULE_STD 1)

project(module-demo VERSION 1.0.0 LANGUAGES CXX)

# We always, always test.
enable_testing()
find_package(Boost 1.80 REQUIRED COMPONENTS unit_test_framework)

if (UNIX OR APPLE)
    include(GNUInstallDirs)
    add_library(hello SHARED)
    add_executable(verify_module)
elseif (WIN32)
    add_library(hello SHARED)
    add_executable(verify_module WIN32)
endif()

set_target_properties(hello PROPERTIES PUBLIC_HEADER src/hello.h)
target_include_directories(hello BEFORE PUBLIC src)
target_sources(hello PUBLIC src/hello.cc)

target_compile_definitions(verify_module PUBLIC BOOST_ALL_NO_LIB)
target_compile_definitions(verify_module PUBLIC BOOST_ALL_DYN_LINK)
target_include_directories(verify_module BEFORE PUBLIC src)
target_sources(verify_module PUBLIC src/verify_module.cc)
target_sources(verify_module
               PUBLIC 
               FILE_SET all_modules 
               TYPE CXX_MODULES 
               FILES src/module.cppm)
target_link_libraries(verify_module hello)

add_test(NAME verify_module COMMAND verify_module)

install(TARGETS hello PUBLIC_HEADER LIBRARY)
