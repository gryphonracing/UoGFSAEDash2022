cmake_minimum_required(VERSION 3.18)

project(GRCDash LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}, Flags: ${CMAKE_CXX_FLAGS}")

if(MSVC)
    add_compile_options(/W4 /WX)
    add_compile_options(
        "$<$<CONFIG:RELEASE>:/O2>"
        "$<$<CONFIG:DEBUG>:/Od>"
    )
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    add_compile_options(
        "$<$<CONFIG:RELEASE>:-O3>"
        "$<$<CONFIG:DEBUG>:-O0>"
    )
endif()

if(${BUILD_FRONTEND})
    find_package(Qt6 CONFIG REQUIRED)
    find_package(runtimeqml CONFIG REQUIRED)
endif()

if(${BUILD_BACKEND})
    find_package(dbcppp CONFIG REQUIRED)
endif()

find_package(fmt CONFIG REQUIRED)
set(CMAKE_THREAD_PREFER_PTHREAD true)
find_package(Threads REQUIRED)

add_subdirectory(src)