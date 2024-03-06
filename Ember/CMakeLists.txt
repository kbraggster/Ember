cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

project(Ember)

# Set the directory containing your header files
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${INCLUDE_DIR}/*.h")

add_library("${PROJECT_NAME}" STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

add_subdirectory(vendor/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC vendor/glfw/include)
target_link_directories(${PROJECT_NAME} PRIVATE vendor/glfw/src)
target_link_libraries(${PROJECT_NAME} glfw)