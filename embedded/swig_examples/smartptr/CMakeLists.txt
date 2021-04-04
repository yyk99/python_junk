#
#
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set_property(SOURCE example.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE example.i PROPERTY SWIG_MODULE_NAME example)

set (_target smartptr)
list(APPEND SWIG_MODULE_${_target}_EXTRA_FLAGS "-interface;_example")

swig_add_library(${_target}
	TYPE SHARED
	LANGUAGE python
	SOURCES
		example.cxx
		example.i
		example.h
		../CMakeLists.txt
		smartptr.h
)

target_link_directories(${_target} PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(${_target} PRIVATE ${Python_LIBRARIES})
source_group(".." FILES ../CMakeLists.txt)
set_property(TARGET ${_target} PROPERTY FOLDER swig_examples)

if (BUILD_TESTS)
	configure_file(runme.py runme.py)
	add_swig_test(${_target})
endif()
