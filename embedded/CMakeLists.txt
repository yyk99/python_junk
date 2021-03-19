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
message(STATUS "Python_VERSION=${Python_VERSION}")

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

add_executable(prog_spam spammodule.cpp)
target_link_directories(prog_spam PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(prog_spam PRIVATE ${Python_LIBRARIES})

# building a module
add_library(spam SHARED spammodule.cpp)
target_compile_definitions(spam PRIVATE -DSPAM_BUILD_MODULE=1)
target_link_directories(spam PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(spam PRIVATE ${Python_LIBRARIES})

add_executable(prog_xx xxmodule.c)
target_compile_definitions(prog_xx PRIVATE -DXX_BUILD_TEST=1)
target_link_directories(prog_xx PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(prog_xx PRIVATE ${Python_LIBRARIES})

add_executable(prog_GM globalmappermodule.cpp)
target_compile_definitions(prog_GM PRIVATE -DGM_BUILD_EMBEDDED=1)
target_link_directories(prog_GM PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(prog_GM PRIVATE ${Python_LIBRARIES})

