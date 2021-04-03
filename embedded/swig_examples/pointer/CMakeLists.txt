#
#
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set_property(SOURCE example.i PROPERTY C ON)
set_property(SOURCE example.i PROPERTY SWIG_MODULE_NAME example)

set (_target pointer)
list(APPEND SWIG_MODULE_${_target}_EXTRA_FLAGS "-interface;_example")

swig_add_library(${_target}
	TYPE SHARED
	LANGUAGE python
#	NO_PROXY
	SOURCES
		example.c
		example.i
)

# message(STATUS "SWIG_MODULE_<name>_REAL_NAME = ${SWIG_MODULE_class_example_REAL_NAME}")

target_link_directories(${_target} PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(${_target} PRIVATE ${Python_LIBRARIES})

set_property(TARGET ${_target} PROPERTY FOLDER swig_examples)

if (BUILD_TESTS)
	configure_file(runme.py runme.py)
	add_swig_test(${_target})
endif()
