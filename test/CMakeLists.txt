cmake_minimum_required(VERSION 3.1)

include_directories("../src/engine")

file(GLOB_RECURSE TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
          ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

if(NOT H9_BOOST_NO_LIB)
  set(BOOST_LIB ${Boost_LIBRARIES})
endif()

add_executable(h9_test ${TEST_SRCS})
target_link_libraries(h9_test engine ${BOOST_LIB})

add_test(NAME h9_unit_test COMMAND h9_test -s)

