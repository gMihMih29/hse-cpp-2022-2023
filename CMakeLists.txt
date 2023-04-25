project(cpp-hse)

cmake_minimum_required(VERSION 3.8)

set(CMAKE_MODULE_PATH              "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

include(cmake/BuildFlags.cmake)
include(cmake/TestSolution.cmake)

find_package(Catch REQUIRED)

include_directories(util)

# 1
add_subdirectory(tasks/multiplication)
add_subdirectory(tasks/hypotenuse)
add_subdirectory(tasks/next_even)
add_subdirectory(tasks/is_leap)
add_subdirectory(tasks/chocolate)
add_subdirectory(tasks/min_divisor)
add_subdirectory(tasks/sum_digits)
add_subdirectory(tasks/fibonacci)
add_subdirectory(tasks/reduce_fraction)


#2
add_subdirectory(tasks/const_diagonal)
add_subdirectory(tasks/variable_diagonal)
add_subdirectory(tasks/palindrome)
add_subdirectory(tasks/password)
add_subdirectory(tasks/range)
add_subdirectory(tasks/factorization)
add_subdirectory(tasks/sort_students)


#3
add_subdirectory(tasks/caesar_cipher)
add_subdirectory(tasks/sort)
add_subdirectory(tasks/stack)
add_subdirectory(tasks/find_last)
