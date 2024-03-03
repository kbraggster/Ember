cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)

project(Matchstick)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable("${PROJECT_NAME}" ${SOURCES})

target_link_libraries("${PROJECT_NAME}" Ember)
