cmake_minimum_required(VERSION 3.27)
project(aoc2023 C)

set(CMAKE_C_STANDARD 11)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/day1/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/day1)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/day2/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/day2)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/day3/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/day3)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/day4/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/day4)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/day5/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/day5)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/day6/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/day6)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/day7/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/day7)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/day8/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/day8)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/day9/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/day9)

add_executable(aoc2023 main.c
        day1/day1.c
        day1/day1.h
        day2/day2.h
        day2/day2.c
        compat/compat.c
        compat/compat.h
        day3/day3.h
        day3/day3.c
        day4/day4.c
        day4/day4.h
        day5/day5.c
        day5/day5.h
        day6/day6.c
        day6/day6.h
        day7/day7.c
        day7/day7.h
        day8/day8.c
        day8/day8.h
        day9/day9.c
        day9/day9.h
)
