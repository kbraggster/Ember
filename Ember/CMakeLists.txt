cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

project(Ember)

# Set the directory containing your header files
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${INCLUDE_DIR}/*.h")

add_library("${PROJECT_NAME}" STATIC ${SOURCE_FILES} ${HEADER_FILES}
        src/Ember/Core/EntryPoint.h
        src/Ember/Core/Log.cpp
        src/Ember/Core/Log.h
        src/Ember/Core/EntryPoint.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/spdlog)

target_include_directories(${PROJECT_NAME} PRIVATE vendor/glfw/include
        PRIVATE vendor/spdlog/include)

target_link_directories(${PROJECT_NAME} PRIVATE vendor/glfw/src
        PRIVATE vendor/spdlog/src)

target_link_libraries(${PROJECT_NAME} glfw spdlog)