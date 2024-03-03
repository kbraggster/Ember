cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(EmberEngine)

set(OSBitness 32)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(OSBitness 64)
endif()

set(OutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set(TargetDir "${CMAKE_SOURCE_DIR}/bin-int/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${TargerDir}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${TargerDir}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OutputDir}")

add_subdirectory(Ember)
add_subdirectory(Matchstick)
