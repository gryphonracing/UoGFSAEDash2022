cmake_minimum_required(VERSION 3.18)

project(GRCDash LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}, Flags: ${CMAKE_CXX_FLAGS}")

if(${BUILD_FRONTEND})
    find_package(Qt6 CONFIG REQUIRED)
endif()

find_package(fmt CONFIG REQUIRED)
set(CMAKE_THREAD_PREFER_PTHREAD true)
find_package(Threads REQUIRED)

add_subdirectory(src)