cmake_minimum_required(VERSION 2.8)

project(serverbattleship)

set(SOURCE_EXE mainserv.cpp)

set(SOURCE_LIB1	field_info.cpp)
add_library(field_info ${SOURCE_LIB1})

set(SOURCE_LIB2 game_info.cpp)
add_library(game_info ${SOURCE_LIB2})

set(SOURCE_LIB3 handler.cpp)
add_library(handler ${SOURCE_LIB3})

add_executable(server ${SOURCE_EXE})
target_link_libraries(server field_info game_info handler)
