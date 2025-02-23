cmake_minimum_required(VERSION 3.0)
project(sizable_bucket_array)

IF (${CMAKE_BUILD_TYPE} MATCHES "debug")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/debug)
  add_definitions(-g -W -Wall -Wextra -std=c++17)
ELSE ()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/release)
  add_definitions(-W -Wall -Wextra -std=c++17)
ENDIF()


# google-test
find_package(GTest REQUIRED)

set(RUNTIME_OUTPUT_DIRECTORY_TEST ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test)
include(CTest)


add_executable(SizableBucketArrayTest
  ${CMAKE_CURRENT_SOURCE_DIR}/test/SizableBucketArrayTest.cpp)

target_link_libraries(SizableBucketArrayTest PRIVATE
  GTest::gtest
  GTest::gmock)

target_include_directories(SizableBucketArrayTest PRIVATE
  ${GTEST_INCLUDE_DIRS}
  ${GMOCK_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(SizableBucketArrayTest
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_TEST})

add_test(NAME SizableBucketArrayTest
  COMMAND SizableBucketArrayTest
  WORKING_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_TEST})
