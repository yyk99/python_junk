#
#
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set_property(SOURCE example.i PROPERTY CPLUSPLUS ON)

swig_add_library(example LANGUAGE python SOURCES 
	example.i 
	example.cxx 
	example.h
)

configure_file(runme.py runme.py)

target_link_directories(example PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(example PRIVATE ${Python_LIBRARIES})

set_property(TARGET example PROPERTY FOLDER swig_examples)