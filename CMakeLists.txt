cmake_minimum_required(VERSION 3.13)
project(ARCHIVING_PROGRAM)

find_package(ZLIB REQUIRED)
find_package(GTest REQUIRED)

add_executable(archiving_program main.cpp)

add_library(archive_lib STATIC archive.cpp)

add_executable(archiving_program_tests tests/test_set.cpp)

target_link_libraries(archive_lib PRIVATE ZLIB::ZLIB)
target_link_libraries(archiving_program PRIVATE archive_lib)
target_link_libraries(archiving_program_tests PRIVATE archive_lib GTest::GTest GTest::Main)

target_include_directories(archive_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${ZLIB_INCLUDE_DIRS})
target_include_directories(archiving_program PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(archiving_program_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()

add_test(NAME test COMMAND archiving_program_tests)