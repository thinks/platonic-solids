# Copyright (C) 2019 Tommy Hinks <tommy.hinks@gmail.com>
# This file is subject to the license terms in the LICENSE file
# found in the top-level directory of this distribution.

cmake_minimum_required(VERSION 3.1)
project(platonic_solids)

if (${CMAKE_SIZEOF_VOID_P} EQUAL "8")
  message(STATUS "platonic_solids: x64")
else ()
  message(STATUS "platonic_solids: x86")
endif ()

# TODO(thinks): ALIAS?
add_library(thinks_platonic_solids INTERFACE)
target_sources(thinks_platonic_solids 
  INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/thinks/platonic_solids/platonic_solids.h)

target_include_directories(thinks_platonic_solids 
  INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR})

option(PLATONIC_SOLIDS_GENERATE_MODELS "If ON, platonic_solids models will be generated." OFF)

if (${PLATONIC_SOLIDS_GENERATE_MODELS})
  message(STATUS "platonic_solids: generate models enabled")
  
  add_subdirectory(external/obj-io)

  add_executable(thinks_generate_platonic_solid_models "")
  target_sources(thinks_generate_platonic_solid_models
    PRIVATE
      thinks/platonic_solids/generate_models.cc)
  target_link_libraries(thinks_generate_platonic_solid_models
    PRIVATE
      thinks_platonic_solids
      thinks_obj_io)

  add_custom_command(
    TARGET thinks_generate_platonic_solid_models
    POST_BUILD    
    COMMAND thinks_generate_platonic_solid_models ${CMAKE_CURRENT_SOURCE_DIR}/models
    COMMENT "platonic_solids: generating models...")  
endif()


