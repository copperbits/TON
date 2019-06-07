cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)

set (TL_UTILS_SOURCE
  tl-utils.hpp
  tl-utils.cpp
  )

add_library(tl-utils STATIC ${TL_UTILS_SOURCE})

target_include_directories(tl-utils PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)
target_link_libraries(tl-utils PUBLIC tl_api ton_crypto )
