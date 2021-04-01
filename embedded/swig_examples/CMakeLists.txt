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
endmacro(add_swig_test)

add_subdirectory(constants)
add_subdirectory(class)
add_subdirectory(simple)
