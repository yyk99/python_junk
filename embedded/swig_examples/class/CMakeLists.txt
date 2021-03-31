#
#
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set_property(SOURCE example.i PROPERTY CPLUSPLUS ON)

set (_target example)

swig_add_library(${_target} 
	LANGUAGE python
#	NO_PROXY 
	SOURCES 
		example.i 
		example.cxx 
		example.h
)

configure_file(runme.py runme.py)

target_link_directories(${_target} PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(${_target} PRIVATE ${Python_LIBRARIES})

set_property(TARGET ${_target} PROPERTY FOLDER swig_examples)
