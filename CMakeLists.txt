cmake_minimum_required(VERSION 2.8)
project(aki)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

set(LIB_SRC
    aki/log.cc
    aki/util.cc
    )

add_library(aki SHARED ${LIB_SRC})
#add_library(aki_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (aki_static PROPERTIES OUTPUT_NAME "aki")

add_executable(test test/test.cc)
add_dependencies(test aki)
target_link_libraries(test aki)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)