cmake_minimum_required(VERSION 3.1)
################################################################################
#                              set project info                                #
################################################################################

set(PROJECT_NAME H9)
set(PROJECT_BRIEF "H9 c++ trading framework")

project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# be nice to vim users
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# silence policy CMP0042 warning by enabling RPATH explicitly
if(APPLE AND NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH true)
endif()
################################################################################
#                              set project options                             #
################################################################################
option(H9_ENABLE_TESTING "Enable unit test" ON)
option(H9_BOOST_NO_LIB "Disable link boost library" OFF)

if(H9_BOOST_NO_LIB)
  add_definitions(-DH9_BOOST_NO_LIB)
endif()
################################################################################
#                              get version of H9                               #
################################################################################
# read content of config.hpp
file(READ "src/engine/version.h" VERSION_H)
# get line containing the version
string(REGEX MATCH "#define H9_VERSION [0-9]+" VERSION_LINE "${VERSION_H}")
# extract version number from line
string(REGEX MATCH " [0-9]+" VERSION_INT "${VERSION_LINE}")
# calculate major, minor, and patch version
math(EXPR H9_VERSION_MAJOR "${VERSION_INT} / 10000")
math(EXPR H9_VERSION_MINOR "( ${VERSION_INT} / 100) % 100")
math(EXPR H9_VERSION_PATCH "${VERSION_INT} % 100")
# create full version string
set(H9_VERSION
    "${H9_VERSION_MAJOR}.${H9_VERSION_MINOR}.${H9_VERSION_PATCH}")
################################################################################
#   set output paths for binaries and libraries if not provided by the user    #
################################################################################
# prohibit in-source builds
if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are not allowed. Please use "
                        "./configure to choose a build directory and "
                        "initialize the build configuration.")
endif()
# set module path appropriately
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# set binary output path if not defined by user
if("${EXECUTABLE_OUTPUT_PATH}" STREQUAL "")
  set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")
endif()
# set library output path if not defined by user, but always set
# library output path to binary output path for Xcode projects
if("${CMAKE_GENERATOR}" STREQUAL "Xcode")
  set(LIBRARY_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}")
elseif("${LIBRARY_OUTPUT_PATH}" STREQUAL "")
  set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/lib")
endif()
################################################################################
#                                compiler setup                                #
################################################################################
# increase max. template depth on GCC and Clang
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang"
   OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
  set(EXTRA_FLAGS "-ftemplate-depth=512 -ftemplate-backtrace-limit=0")
endif()

# set build default build type to RelWithDebInfo if not set
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

# add extra flags
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${EXTRA_FLAGS})
################################################################################
#                                Doxygen setup                                 #
################################################################################
# check for doxygen and add custom "doc" target to Makefile
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in"
                 "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile"
                 @ONLY)
  add_custom_target(doc "${DOXYGEN_EXECUTABLE}"
                    "${CMAKE_HOME_DIRECTORY}/Doxyfile"
                    WORKING_DIRECTORY "${CMAKE_HOME_DIRECTORY}"
                    COMMENT "Generating API documentation with Doxygen"
                    VERBATIM)
endif(DOXYGEN_FOUND)
################################################################################
#                                Boost setup                                   #
################################################################################
find_package(Boost 1.58 REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()
################################################################################
#                       set inclue paths for subprojects                       #
################################################################################
set(LIBH9_INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/engine")

# Build the targets
add_subdirectory(src)

# enable tests if not disabled
if (H9_ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()

# all projects need the headers of the core components
include_directories("${LIBH9_INCLUDE_DIRS}")
################################################################################
#                                print summary                                 #
################################################################################
# collect all compiler flags
string(TOUPPER "${CMAKE_BUILD_TYPE}" UPPER_BUILD_TYPE)
set(ALL_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${UPPER_BUILD_TYPE}}")

# done
if(NOT H9_NO_SUMMARY)
  message(STATUS
        "\n====================|  Build Summary  |===================="
        "\n"
        "\nLibh9 version:     ${H9_VERSION}"
        "\n"
        "\nBuild type:        ${CMAKE_BUILD_TYPE}"
        "\nBuild static:      ${H9_BUILD_STATIC}"
        "\nBuild static only: ${H9_BUILD_STATIC_ONLY}"
        "\n"
        "\nBoost version:     ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}"
        "\nBoost include:     ${Boost_INCLUDE_DIRS}"
        "\nBoost library:     ${Boost_LIBRARY_DIRS}"
        "\n"
        "\nCXX:               ${CMAKE_CXX_COMPILER}"
        "\nCXXFLAGS:          ${ALL_CXX_FLAGS}"
        "\nLIBRARIES:         ${LD_FLAGS}"
        "\n"
        "\nSource directory:  ${CMAKE_CURRENT_SOURCE_DIR}"
        "\nBuild directory:   ${CMAKE_CURRENT_BINARY_DIR}"
        "\nExecutable path:   ${EXECUTABLE_OUTPUT_PATH}"
        "\nLibrary path:      ${LIBRARY_OUTPUT_PATH}"
        "\nInstall prefix:    ${CMAKE_INSTALL_PREFIX}"
        "\nGenerator:         ${CMAKE_GENERATOR}"
        "\n"
        "\n===========================================================\n")
endif()
################################################################################
#                                THE END                                       #
################################################################################
