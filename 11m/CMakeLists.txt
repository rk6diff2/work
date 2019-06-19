cmake_minimum_required(VERSION 3.13)
project(untitled1 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm")
find_package(X11 REQUIRED)

message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})

file(GLOB MANY_SOURCES ./main.c
        rotate_line.c)


file(GLOB ALL_HEADERS rotate_line.h)

add_executable(main.out ${MANY_SOURCES} ${ALL_HEADERS})
target_link_libraries(main.out ${X11_LIBRARIES})
target_link_libraries(main.out m)
