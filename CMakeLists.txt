cmake_minimum_required(VERSION 3.1)

project(EnvArguments VERSION 1.0
                     DESCRIPTION "Utility to work with command line arguments"
                     LANGUAGES CXX)

# place binaries and libraries according to GNU standards
include(GNUInstallDirs)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# we use this to get code coverage
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

set(CMAKE_VERBOSE_MAKEFILE OFF)

add_subdirectory(src)

include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest) # sets BUILD_TESTING=ON
endif()

option(PACKAGE_TESTS "Build the tests" ON)
if(BUILD_TESTING AND PACKAGE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

