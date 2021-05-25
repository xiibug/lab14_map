cmake_minimum_required(VERSION 2.8) 

set(PROJECT_NAME SortedMap) 
project(${PROJECT_NAME}) 

set(TMap TMap) 
set(main main)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE) 
if(NOT CMAKE_BUILD_TYPE) 
  set(CMAKE_BUILD_TYPE Release) 
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TMap) 

add_subdirectory(gtest)
add_subdirectory(TMap)
add_subdirectory(main)
add_subdirectory(test)

