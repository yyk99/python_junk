#
#
#

add_library(MapperLib STATIC
	ControlCenter.cpp
	ControlCenter.h
	Mapper.cpp 
	Mapper.h
	)
add_executable(MapperApp MapperMain.cpp)
set_property(TARGET MapperApp PROPERTY FOLDER apps)


# Configure the wrapper module

if (SWIG_FOUND)
	# include dir for Mapper.h & ControlCenter.h
	include_directories(${CMAKE_CURRENT_SOURCE_DIR})

	set_property(SOURCE mappermodule.i PROPERTY CPLUSPLUS ON)
	#set_property(SOURCE mappermodule.i PROPERTY SWIG_MODULE_NAME mappermodule)
	swig_add_library(mappermodule TYPE STATIC LANGUAGE python SOURCES mappermodule.i)
	target_link_libraries(mappermodule PRIVATE MapperLib)
	target_link_directories(mappermodule PRIVATE ${Python_LIBRARY_DIRS})
	target_link_libraries(mappermodule PRIVATE ${Python_LIBRARIES})

endif()

if (BUILD_TESTS)

	add_executable(test_Mapper Mapper.cpp Mapper.h)
	target_compile_definitions(test_Mapper PRIVATE -DMAPPER_BUILD_TEST=1)
	set_property(TARGET test_Mapper PROPERTY FOLDER tests)
	#target_link_directories(test_GM PRIVATE ${Python_LIBRARY_DIRS})
	#target_link_libraries(test_GM PRIVATE ${Python_LIBRARIES})
	target_link_libraries(test_Mapper PRIVATE ${GTEST_BOTH_LIBS})
	add_test(test_Mapper test_Mapper)
	
	if (SWIG_FOUND)
		add_executable(test_mappermodule mappermodule_test.cpp)
		#target_compile_definitions(test_mappermodule PRIVATE -DMAPPER_BUILD_TEST=1)
		set_property(TARGET test_mappermodule PROPERTY FOLDER tests)
		target_link_directories(test_mappermodule PRIVATE ${Python_LIBRARY_DIRS})
		target_link_libraries(test_mappermodule PRIVATE ${Python_LIBRARIES})
		target_link_libraries(test_mappermodule PRIVATE ${GTEST_BOTH_LIBS})
		target_link_libraries(test_mappermodule PRIVATE mappermodule)
		add_test(test_mappermodule test_mappermodule)
	endif()

endif(BUILD_TESTS)
