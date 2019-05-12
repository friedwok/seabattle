cmake_minimum_required(VERSION 2.8)

project(clientbattleship)

set(SOURCE_EXE client.cpp)

set(SOURCE_LIB1 field_info.cpp)
add_library(field_info ${SOURCE_LIB1})

set(SOURCE_LIB2 fill_the_field.cpp)
add_library(fill_the_field ${SOURCE_LIB2})

set(SOURCE_LIB3 pregame.cpp)
add_library(pregame ${SOURCE_LIB3})

set(SOURCE_LIB4 stage2.cpp)
add_library(stage2 ${SOURCE_LIB4})

set(SOURCE_LIB5 startgame.cpp)
add_library(startgame ${SOURCE_LIB5})

set(SOURCE_LIB6 wordtest.cpp)
add_library(wordtest ${SOURCE_LIB6})

add_executable(client ${SOURCE_EXE})
target_link_libraries(client field_info fill_the_field pregame stage2 startgame wordtest)
