cmake_minimum_required(VERSION 3.0.2)

file(MAKE_DIRECTORY auto/tl)

set(TL_TON_API
  ${CMAKE_CURRENT_SOURCE_DIR}/auto/tl/ton_api.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/auto/tl/ton_api.h
  ${CMAKE_CURRENT_SOURCE_DIR}/auto/tl/ton_api.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/auto/tl/ton_api_json.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/auto/tl/ton_api_json.h
  PARENT_SCOPE
)

set(TL_LITE_API
  ${CMAKE_CURRENT_SOURCE_DIR}/auto/tl/lite_api.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/auto/tl/lite_api.h
  ${CMAKE_CURRENT_SOURCE_DIR}/auto/tl/lite_api.hpp
  PARENT_SCOPE
)

set(TL_TONLIB_API
  ${CMAKE_CURRENT_SOURCE_DIR}/auto/tl/tonlib_api.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/auto/tl/tonlib_api.h
  ${CMAKE_CURRENT_SOURCE_DIR}/auto/tl/tonlib_api.hpp
  PARENT_SCOPE
)

set(TL_TONLIB_API_JSON
  ${CMAKE_CURRENT_SOURCE_DIR}/auto/tl/tonlib_api_json.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/auto/tl/tonlib_api_json.h
  PARENT_SCOPE
)

set(TL_GENERATE_COMMON_SOURCE
  generate_common.cpp

  tl_json_converter.cpp
  tl_writer_cpp.cpp
  tl_writer_h.cpp
  tl_writer_hpp.cpp
  tl_writer_td.cpp
  tl_writer_jni_cpp.cpp
  tl_writer_jni_h.cpp

  tl_json_converter.h
  tl_writer_cpp.h
  tl_writer_h.h
  tl_writer_hpp.h
  tl_writer_td.h
  tl_writer_jni_cpp.h
  tl_writer_jni_h.h
)

set(TL_GENERATE_JAVA_SOURCE
  generate_java.cpp
  tl_writer_java.cpp

  tl_writer_java.h
)
add_executable(tonlib_generate_java_api ${TL_GENERATE_JAVA_SOURCE})
target_link_libraries(tonlib_generate_java_api PRIVATE tdtl)

if (NOT CMAKE_CROSSCOMPILING)
  find_program(PHP_EXECUTABLE php)

  set(GenerateCommonCmd generate_common)
  add_executable(generate_common ${TL_GENERATE_COMMON_SOURCE})
  target_link_libraries(generate_common PRIVATE tdtl tdutils)
  add_custom_target(tl_generate_common
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${GenerateCommonCmd}
    COMMENT "Generate common tl source files"
    DEPENDS generate_common scheme/ton_api.tlo
  )
  if (TONLIB_ENABLE_JNI)
    target_compile_definitions(generate_common PRIVATE TONLIB_ENABLE_JNI=1)
  endif()
else()
  add_custom_target(tl_generate_common)
endif()
