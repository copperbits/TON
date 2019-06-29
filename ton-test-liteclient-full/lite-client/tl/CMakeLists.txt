cmake_minimum_required(VERSION 3.0.2)
add_subdirectory(generate)
set_source_files_properties(${TL_TON_API} PROPERTIES GENERATED TRUE)
add_library(tl_api STATIC 
	${TL_TON_API} 
	tl/tl_object_parse.h 
	tl/tl_object_store.h 
	tl/TlObject.h)
add_dependencies(tl_api tl_generate_common)
target_link_libraries(tl_api tdutils)
target_include_directories(tl_api PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/..
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/../crypto/ $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/generate)

if (TONLIB_ENABLE_JNI)
  set(TL_JNI_OBJECT
    tl/tl_jni_object.cpp
    tl/tl_jni_object.h
  )
else()
  set(TL_JNI_OBJECT)
endif()
set_source_files_properties(${TL_TONLIB_API} PROPERTIES GENERATED TRUE)
add_library(tl_tonlib_api STATIC ${TL_TONLIB_API} tl/tl_object_parse.h tl/tl_object_store.h tl/TlObject.h
	${TL_JNI_OBJECT})
add_dependencies(tl_tonlib_api tl_generate_common)
target_link_libraries(tl_tonlib_api tdutils)
target_include_directories(tl_tonlib_api PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/..
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/../crypto/
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/generate )
