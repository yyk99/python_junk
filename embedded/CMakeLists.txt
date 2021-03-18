#
#
#
project(embedded_primer)
cmake_minimum_required(VERSION 3.13)

find_package (Python COMPONENTS Interpreter Development)

if (NOT Python_FOUND)
	message(FATAL "Python not found")
endif()

include_directories(${Python_INCLUDE_DIRS})

message(STATUS "Python_LIBRARIES=${Python_LIBRARIES}")

add_executable(prog_11 very_high_level.cpp)
target_link_directories(prog_11 PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(prog_11 PRIVATE ${Python_LIBRARIES})

configure_file(multiply.py multiply.py)
configure_file(test_numarg.py test_numarg.py)
configure_file(foo.py foo.py)

add_executable(prog_13 pure_embedding.cpp)
target_link_directories(prog_13 PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(prog_13 PRIVATE ${Python_LIBRARIES})

add_executable(prog_20 pure_embedding2.cpp)
target_link_directories(prog_20 PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(prog_20 PRIVATE ${Python_LIBRARIES})

add_executable(globalmapper globalmapper.cpp)
target_link_directories(globalmapper PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(globalmapper PRIVATE ${Python_LIBRARIES})
