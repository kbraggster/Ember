cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

project(Matchstick)

# Recursively find source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable("${PROJECT_NAME}" ${SOURCES})

# Set output directory
set(TargetDir ${TargetDir}/${PROJECT_NAME})
set(ObjDir ${ObjDir}/${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${TargetDir}"
)

# Add Ember library
target_link_libraries("${PROJECT_NAME}" Ember)