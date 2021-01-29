link_libraries(ws2_32)

cmake_minimum_required(VERSION 3.15)
project(wedServer C)

set(CMAKE_C_STANDARD 99)

add_executable(wedServer main.c)
