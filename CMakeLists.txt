cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g -Wall -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall -Werror -Wpedantic")

include(cmake/CPM.cmake)

CPMAddPackage("gh:libcpr/cpr#1.10.5")

project(mpsslib LANGUAGES CXX)
add_library(mpsslib SHARED)

file(GLOB_RECURSE SOURCES "src/*")
file(GLOB_RECURSE HEADERS "include/*")

target_sources(mpsslib PRIVATE ${SOURCES} PUBLIC ${HEADERS})

target_include_directories(mpsslib PUBLIC "include")
target_link_libraries(mpsslib cpr)

CPMAddPackage("gh:catchorg/Catch2@3.7.0")
add_executable(test_mpsslib test/main.cpp)
target_link_libraries(test_mpsslib Catch2::Catch2WithMain mpsslib)
enable_testing()
add_test(test_mpsslib test_mpsslib)