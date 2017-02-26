cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(engine CXX C)

set(ENGINE_HEADER
    common.h
    version.h
    datetime.h
)
set(ENGINE_SRC
  datetime.cpp
)

if(NOT H9_BOOST_NO_LIB)
  set(BOOST_LIB ${Boost_LIBRARIES})
endif()

add_library(engine STATIC  ${ENGINE_HEADER} ${ENGINE_SRC})
target_link_libraries(engine ${BOOST_LIB})
