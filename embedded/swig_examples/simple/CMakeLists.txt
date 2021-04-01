#
# simple
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set_property(SOURCE example.i PROPERTY C ON)
set_property(SOURCE example.i PROPERTY SWIG_MODULE_NAME example)

set (_target simple)

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
	add_swig_test(${_target})
endif()
