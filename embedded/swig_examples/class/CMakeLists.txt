#
#
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set_property(SOURCE example.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE example.i PROPERTY SWIG_MODULE_NAME example)

set (_target class_example)

swig_add_library(${_target} 
	TYPE SHARED
	LANGUAGE python
#	NO_PROXY 
	SOURCES 
		example.i 
		example.cxx 
		example.h
)

target_link_directories(${_target} PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(${_target} PRIVATE ${Python_LIBRARIES})

set_property(TARGET ${_target} PROPERTY FOLDER swig_examples)

if (BUILD_TESTS)
	configure_file(runme.py runme.py)
	
	add_executable(test_example_class example_class_test.cpp runme.py)
	#target_compile_definitions(test_mappermodule PRIVATE -DMAPPER_BUILD_TEST=1)
	set_property(TARGET test_example_class PROPERTY FOLDER tests)
	target_link_directories(test_example_class PRIVATE ${Python_LIBRARY_DIRS})
	target_link_libraries(test_example_class PRIVATE ${Python_LIBRARIES})
	target_link_libraries(test_example_class PRIVATE ${GTEST_BOTH_LIBS})
	target_link_libraries(test_example_class PRIVATE ${_target})
	add_test(test_example_class test_example_class)
endif()
