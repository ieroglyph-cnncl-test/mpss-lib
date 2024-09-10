cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/BuildConfig.cmake)
include(cmake/CPM.cmake)

CPMAddPackage("gh:fmtlib/fmt#11.0.2")
CPMAddPackage("gh:libcpr/cpr#1.10.5")
CPMAddPackage("gh:nlohmann/json@3.11.3")

project(mpsslib LANGUAGES CXX)
add_library(mpsslib SHARED)

file(GLOB_RECURSE SOURCES "src/*")
file(GLOB_RECURSE HEADERS "include/*")

target_sources(mpsslib PRIVATE ${SOURCES} PUBLIC ${HEADERS})

target_include_directories(mpsslib PUBLIC "include")
target_link_libraries(mpsslib cpr nlohmann_json::nlohmann_json fmt::fmt)

CPMAddPackage("gh:catchorg/Catch2@3.7.0")
add_executable(test_mpsslib test/main.cpp)
target_link_libraries(test_mpsslib Catch2::Catch2WithMain mpsslib)
enable_testing()
add_test(test_mpsslib test_mpsslib)
