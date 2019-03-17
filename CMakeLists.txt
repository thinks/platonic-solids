# Copyright (C) 2019 Tommy Hinks <tommy.hinks@gmail.com>
# This file is subject to the license terms in the LICENSE file
# found in the top-level directory of this distribution.

cmake_minimum_required(VERSION 3.1)
project(platonic_solids)

# TODO(thinks): ALIAS?
add_library(thinks_platonic_solids INTERFACE)
target_sources(thinks_platonic_solids 
  INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/thinks/platonic_solids/platonic_solids.h
)

target_include_directories(thinks_platonic_solids 
  INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

option(PLATONIC_SOLIDS_RUN_TESTS "If ON, platonic_solids tests will be run." OFF)

if(${PLATONIC_SOLIDS_RUN_TESTS})
  # Enable CTest. This will set BUILD_TESTING to ON unless otherwise 
  # specified on the command line.
  include(CTest)
  enable_testing()
  message(STATUS "platonic_solids: tests enabled")
endif()

if (BUILD_TESTING)
  include(CTest)
  enable_testing()
  add_subdirectory(external/Catch2)

  add_executable(thinks_platonic_solids_test "")
  target_sources(thinks_platonic_solids_test
    PRIVATE
      thinks/platonic_solids/platonic_solids_test.cc)
  target_link_libraries(thinks_platonic_solids_test
    PRIVATE
      thinks_platonic_solids
      Catch2::Catch2)
  set_target_properties(thinks_platonic_solids_test PROPERTIES CXX_STANDARD 11)
  add_test(NAME thinks_platonic_solids_test COMMAND thinks_platonic_solids_test)
endif()
