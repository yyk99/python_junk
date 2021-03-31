#
# simple
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set_property(SOURCE example.i PROPERTY C ON)

set (_target simple_example)

swig_add_library(${_target} 
	TYPE STATIC
	LANGUAGE python
	NO_PROXY 
	SOURCES 
		example.i 
		example.c
#		example.h
)

configure_file(runme.py runme.py)

target_link_directories(${_target} PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(${_target} PRIVATE ${Python_LIBRARIES})

set_property(TARGET ${_target} PROPERTY FOLDER swig_examples)

if (BUILD_TESTS)
	add_executable(test_example_simple example_simple_test.cpp)
	#target_compile_definitions(test_mappermodule PRIVATE -DMAPPER_BUILD_TEST=1)
	set_property(TARGET test_example_simple PROPERTY FOLDER tests)
	target_link_directories(test_example_class PRIVATE ${Python_LIBRARY_DIRS})
	target_link_libraries(test_example_simple PRIVATE ${Python_LIBRARIES})
	target_link_libraries(test_example_simple PRIVATE ${GTEST_BOTH_LIBS})
	target_link_libraries(test_example_simple PRIVATE ${_target})
	add_test(test_example_simple test_example_simple)
endif()
