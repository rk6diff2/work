cmake_minimum_required(VERSION 2.9)
project(rk1 C)
find_package(X11 REQUIRED)

message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

set(CMAKE_C_STANDARD 99)

include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})

add_executable(main.out main.c)

target_link_libraries(main.out ${X11_LIBRARIES})
