#
#
#
project(embedded_primer)
cmake_minimum_required(VERSION 3.13)

option (BUILD_TESTS "Build tests" OFF)

# I do not want to find a 3rdparty python installation.
set(Python_FIND_REGISTRY "NEVER")

message (STATUS "Python_FIND_REGISTRY=${Python_FIND_REGISTRY}")

find_package (Python COMPONENTS Interpreter Development REQUIRED)

message(STATUS "Python_VERSION=${Python_VERSION}")
message(STATUS "Python_LIBRARIES=${Python_LIBRARIES}")

# SWIG

# set(SWIG_EXECUTABLE "" CACHE FILEPATH "Swig executable")

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL  "3.14") 
    cmake_policy(SET CMP0086 OLD)
endif()

find_package(SWIG 3.0 COMPONENTS python )

if(SWIG_FOUND)
    message(STATUS "SWIG found: ${SWIG_EXECUTABLE}")
    include (UseSWIG)
else()
    message(STATUS "SWIG NOT found. Some projects will be unavailable")
endif()

# Configure ...

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(${Python_INCLUDE_DIRS})


if(BUILD_TESTS)
    enable_testing()

    include(ExternalProject)

    list(APPEND CACHE_ARGS "-DBUILD_GMOCK:BOOL=OFF")
#    list(APPEND CACHE_ARGS "-DBUILD_GTEST:BOOL=ON") # not used in 1.8.1
    list(APPEND CACHE_ARGS "-Dgtest_force_shared_crt:BOOL=ON")
    string(REPLACE ";" "$<SEMICOLON>" CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}")

    list(APPEND CACHE_ARGS "-DCMAKE_CONFIGURATION_TYPES:STRING=${CONFIGURATION_TYPES}")

    ExternalProject_Add(
        googletest-build
        GIT_REPOSITORY    https://github.com/google/googletest.git
        GIT_TAG           "release-1.8.1"
        SOURCE_DIR        "${CMAKE_BINARY_DIR}/googletest-src"
        BINARY_DIR        "${CMAKE_BINARY_DIR}/googletest-build"
        TEST_COMMAND      ""
        CMAKE_ARGS        ${CACHE_ARGS}
        INSTALL_COMMAND   ""
#        BUILD_COMMAND     ""
    )

    set(GTEST_SOURCE_DIR ${CMAKE_BINARY_DIR}/googletest-src/googletest)
    set(GTEST_ROOT ${GTEST_SOURCE_DIR})
    set(GTEST_INCLUDE_DIR ${GTEST_ROOT}/include)
    if(WIN32)
      set(GTEST_BOTH_LIBS
        ${CMAKE_BINARY_DIR}/googletest-build/googletest/$<CONFIG>/gtest_main$<$<CONFIG:Debug>:d>.lib
        ${CMAKE_BINARY_DIR}/googletest-build/googletest/$<CONFIG>/gtest$<$<CONFIG:Debug>:d>.lib
        )
    else()
      set(GTEST_BOTH_LIBS
        ${CMAKE_BINARY_DIR}/googletest-build/googletest/$<CONFIG>/libgtest_main.a
        ${CMAKE_BINARY_DIR}/googletest-build/googletest/$<CONFIG>/libgtest.a
        -pthread
        )
    endif()      

    # MS VS2012 needs this to compile tupe templates
    add_definitions(-D_VARIADIC_MAX=10)
    include_directories(${GTEST_INCLUDE_DIR} ${GTEST_ROOT})
endif(BUILD_TESTS)

#
# Configure projects
#

add_executable(prog_11 very_high_level.cpp)
target_link_directories(prog_11 PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(prog_11 PRIVATE ${Python_LIBRARIES})
set_property(TARGET prog_11 PROPERTY FOLDER apps)

configure_file(py_samples/multiply.py multiply.py)
configure_file(py_samples/test_numarg.py test_numarg.py)
configure_file(py_samples/foo.py foo.py)

add_executable(prog_13 pure_embedding.cpp)
target_link_directories(prog_13 PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(prog_13 PRIVATE ${Python_LIBRARIES})
set_property(TARGET prog_13 PROPERTY FOLDER apps)

add_executable(prog_20 pure_embedding2.cpp)
target_link_directories(prog_20 PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(prog_20 PRIVATE ${Python_LIBRARIES})
set_property(TARGET prog_20 PROPERTY FOLDER apps)

add_executable(prog_spam spammodule.cpp)
target_link_directories(prog_spam PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(prog_spam PRIVATE ${Python_LIBRARIES})
set_property(TARGET prog_spam PROPERTY FOLDER apps)

# building a module
add_library(spam SHARED spammodule.cpp spam-setup.py.template)
target_compile_definitions(spam PRIVATE -DSPAM_BUILD_MODULE=1)
target_link_directories(spam PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(spam PRIVATE ${Python_LIBRARIES})
set_property(TARGET spam PROPERTY FOLDER libs)

message(STATUS "Python_LIBRARY_RELEASE=${Python_LIBRARY_RELEASE}")
set (SPAM_MODULE_LIBRARIES "'${Python_LIBRARY_RELEASE}'")
configure_file(spam-setup.py.template spam-setup.py)

add_executable(prog_xx xxmodule.c)
target_compile_definitions(prog_xx PRIVATE -DXX_BUILD_TEST=1)
target_link_directories(prog_xx PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(prog_xx PRIVATE ${Python_LIBRARIES})
set_property(TARGET prog_xx PROPERTY FOLDER apps)

add_executable(prog_GM globalmappermodule.cpp)
target_compile_definitions(prog_GM PRIVATE -DGM_BUILD_EMBEDDED=1)
target_link_directories(prog_GM PRIVATE ${Python_LIBRARY_DIRS})
target_link_libraries(prog_GM PRIVATE ${Python_LIBRARIES})
set_property(TARGET prog_GM PROPERTY FOLDER apps)

add_subdirectory(Mapper)

add_subdirectory(swig_examples)

#
# Configure tests
#
if (BUILD_TESTS)

    add_executable(test_GM globalmappermodule.cpp)
    set_property(TARGET test_GM PROPERTY FOLDER tests)

    target_compile_definitions(test_GM PRIVATE -DGM_BUILD_TEST=1)
    target_link_directories(test_GM PRIVATE ${Python_LIBRARY_DIRS})
    target_link_libraries(test_GM PRIVATE ${Python_LIBRARIES})
    target_link_libraries(test_GM PRIVATE ${GTEST_BOTH_LIBS})
    add_test(test_GM test_GM)

endif(BUILD_TESTS)
