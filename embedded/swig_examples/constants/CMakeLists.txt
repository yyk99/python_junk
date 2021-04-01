#
#
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set_property(SOURCE example.i PROPERTY C ON)
set_property(SOURCE example.i PROPERTY SWIG_MODULE_NAME example)

set (_target constants)
list(APPEND SWIG_MODULE_${_target}_EXTRA_FLAGS "-interface;_example")

swig_add_library(${_target}
	TYPE SHARED
	LANGUAGE python
#	NO_PROXY
	SOURCES
		example.i
#		example.h
)

# message(STATUS "SWIG_MODULE_<name>_REAL_NAME = ${SWIG_MODULE_class_example_REAL_NAME}")

target_link_directories(${_target} PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(${_target} PRIVATE ${Python_LIBRARIES})

set_property(TARGET ${_target} PROPERTY FOLDER swig_examples)

if (BUILD_TESTS)
	configure_file(runme.py runme.py)

	add_executable(test_example_constants example_constants_test.cpp runme.py ../CMakeLists.txt)
	target_include_directories(test_example_constants PRIVATE ${GTEST_INCLUDE_DIR} ${GTEST_ROOT})
	target_link_directories(test_example_constants PRIVATE ${Python_LIBRARY_DIRS})
	target_link_libraries(test_example_constants PRIVATE ${Python_LIBRARIES})
	target_link_libraries(test_example_constants PRIVATE ${GTEST_BOTH_LIBS})
	target_link_libraries(test_example_constants PRIVATE ${_target})
	add_test(test_example_constants test_example_constants)
	set_property(TARGET test_example_constants PROPERTY FOLDER tests)

	source_group(".." FILES ../CMakeLists.txt)
endif()
