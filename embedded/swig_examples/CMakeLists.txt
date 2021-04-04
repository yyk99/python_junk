#
#
#

macro(add_swig_test name )
    configure_file(runme.py runme.py)

	set(_t test_example_${name})

	add_executable(${_t} example_${name}_test.cpp runme.py ../CMakeLists.txt)
	target_include_directories(${_t} PRIVATE ${GTEST_INCLUDE_DIR} ${GTEST_ROOT})
	target_link_directories(${_t} PRIVATE ${Python_LIBRARY_DIRS})
	target_link_libraries(${_t} PRIVATE ${Python_LIBRARIES})
	target_link_libraries(${_t} PRIVATE ${GTEST_BOTH_LIBS})
	target_link_libraries(${_t} PRIVATE ${_target})
	add_test(${_t} ${_t})
	set_property(TARGET ${_t} PROPERTY FOLDER tests)

	source_group(".." FILES ../CMakeLists.txt)
endmacro(add_swig_test)

add_subdirectory(callback)
add_subdirectory(class)
add_subdirectory(constants)
add_subdirectory(contract)
add_subdirectory(docstrings)
add_subdirectory(enum)
add_subdirectory(exception)
add_subdirectory(exceptproxy)
add_subdirectory(extend)
add_subdirectory(funcptr)
add_subdirectory(funcptr2)
add_subdirectory(functor)
add_subdirectory(import)
add_subdirectory(multimap)
add_subdirectory(operator)
add_subdirectory(pointer)
add_subdirectory(reference)
add_subdirectory(simple)
add_subdirectory(smartptr)
add_subdirectory(std_map)
add_subdirectory(std_vector)
add_subdirectory(template)
add_subdirectory(varargs)
add_subdirectory(variables)

# end of file
