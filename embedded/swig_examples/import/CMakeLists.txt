#
#
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# bar
set (_target bar)
set_property(SOURCE ${_target}.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE ${_target}.i PROPERTY SWIG_MODULE_NAME ${_target})
#list(APPEND SWIG_MODULE_${_target}_EXTRA_FLAGS "-interface;_example")
swig_add_library(${_target}
	TYPE SHARED
	LANGUAGE python
	SOURCES
		${_target}.i
		${_target}.h
)
target_link_directories(${_target} PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(${_target} PRIVATE ${Python_LIBRARIES})
set_property(TARGET ${_target} PROPERTY FOLDER swig_examples/import)

# base
set (_target base)
set_property(SOURCE ${_target}.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE ${_target}.i PROPERTY SWIG_MODULE_NAME ${_target})
#list(APPEND SWIG_MODULE_${_target}_EXTRA_FLAGS "-interface;_example")
swig_add_library(${_target}
	TYPE SHARED
	LANGUAGE python
	SOURCES
		${_target}.i
		${_target}.h
)
target_link_directories(${_target} PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(${_target} PRIVATE ${Python_LIBRARIES})
set_property(TARGET ${_target} PROPERTY FOLDER swig_examples/import)

# foo
set (_target foo)
set_property(SOURCE ${_target}.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE ${_target}.i PROPERTY SWIG_MODULE_NAME ${_target})
#list(APPEND SWIG_MODULE_${_target}_EXTRA_FLAGS "-interface;_example")
swig_add_library(${_target}
	TYPE SHARED
	LANGUAGE python
	SOURCES
		${_target}.i
		${_target}.h
)
target_link_directories(${_target} PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(${_target} PRIVATE ${Python_LIBRARIES})
set_property(TARGET ${_target} PROPERTY FOLDER swig_examples/import)

# spam
set (_target spam)
set_property(SOURCE ${_target}.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE ${_target}.i PROPERTY SWIG_MODULE_NAME ${_target})
#list(APPEND SWIG_MODULE_${_target}_EXTRA_FLAGS "-interface;_example")
swig_add_library(${_target}
	TYPE SHARED
	LANGUAGE python
	SOURCES
		${_target}.i
		${_target}.h
)
target_link_directories(${_target} PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(${_target} PRIVATE ${Python_LIBRARIES})
set_property(TARGET ${_target} PROPERTY FOLDER swig_examples/import)

if (BUILD_TESTS)
	configure_file(runme.py runme.py)
	add_swig_test(import)
	target_link_libraries(test_example_import 
		PRIVATE
			foo
			bar
			base
	)
endif()
