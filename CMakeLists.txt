cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(EmberEngine)

set(TargetDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_PROCESSOR}")
set(ObjDir "${CMAKE_SOURCE_DIR}/bin-int/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_PROCESSOR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ObjDir}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ObjDir}/lib")

add_subdirectory(Ember)
add_subdirectory(Matchstick)

set_target_properties(Matchstick PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${TargetDir}/Matchstick"
)

set_target_properties(Ember PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${ObjDir}/Ember"
        LIBRARY_OUTPUT_DIRECTORY "${ObjDir}/Ember"
        RUNTIME_OUTPUT_DIRECTORY "${ObjDir}/Ember"
)