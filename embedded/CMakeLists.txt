#
#
#
project(embedded_primer)
cmake_minimum_required(VERSION 3.18)

find_package (Python COMPONENTS Interpreter Development)

if (NOT Python_FOUND)
	message(FATAL "Python not found")
endif()

include_directories(${Python_INCLUDE_DIRS})

message(STATUS "Python_LIBRARIES=${Python_LIBRARIES}")

add_executable(prog_11 very_high_level.cpp)
target_link_directories(prog_11 PRIVATE ${Python_LIBRARY_DIRS})
