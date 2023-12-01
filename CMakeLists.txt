cmake_minimum_required(VERSION 3.27)
project(aoc2023 C)

set(CMAKE_C_STANDARD 11)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/day1/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/day1)

add_executable(aoc2023 main.c
        day1/day1.c
        day1/day1.h
)
