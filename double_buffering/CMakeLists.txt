cmake_minimum_required(VERSION 2.4)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -Werror")

project(double_buffer)

add_executable(double_buffer double_buffer.c)
target_link_libraries(double_buffer pthread)
