#
#
#

add_library(MapperLib
	ControlCenter.cpp
	ControlCenter.h
	Mapper.cpp 
	Mapper.h
	)
add_executable(MapperApp MapperMain.cpp)

if (BUILD_TESTS)

add_executable(test_Mapper Mapper.cpp Mapper.h)
target_compile_definitions(test_Mapper PRIVATE -DMAPPER_BUILD_TEST=1)
#target_link_directories(test_GM PRIVATE ${Python_LIBRARY_DIRS})
#target_link_libraries(test_GM PRIVATE ${Python_LIBRARIES})
target_link_libraries(test_Mapper PRIVATE ${GTEST_BOTH_LIBS})
add_test(test_Mapper test_Mapper)

endif(BUILD_TESTS)


