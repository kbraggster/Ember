cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

project(Ember)

# Set the directory containing your header files
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Recursively find source and header files
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${INCLUDE_DIR}/*.h")

add_library("${PROJECT_NAME}" STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

# Set output directory
set(TargetDir ${TargetDir}/${PROJECT_NAME})
set(ObjDir ${ObjDir}/${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${TargetDir}"
        ARCHIVE_OUTPUT_DIRECTORY "${ObjDir}"
        LIBRARY_OUTPUT_DIRECTORY "${ObjDir}"
)

# Add precompiled header
target_precompile_headers(${PROJECT_NAME} PRIVATE src/empch.h)

# Add libraries
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glad)

# Set output directory for libraries
set(OutputDir ${EmberOutputDir})
set_target_properties(glfw PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${ObjDir}
        LIBRARY_OUTPUT_DIRECTORY ${ObjDir})
set_target_properties(spdlog PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${ObjDir}
        LIBRARY_OUTPUT_DIRECTORY ${ObjDir})
set_target_properties(imgui PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${ObjDir}
        LIBRARY_OUTPUT_DIRECTORY ${ObjDir})
set_target_properties(glad PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${ObjDir}
        LIBRARY_OUTPUT_DIRECTORY ${ObjDir})

# Include and link libraries
target_include_directories(${PROJECT_NAME} PRIVATE vendor/glfw/include
        PRIVATE vendor/spdlog/include
        PRIVATE vendor/imgui
        PRIVATE vendor/glad)

target_link_directories(${PROJECT_NAME} PRIVATE vendor/glfw/src
        PRIVATE vendor/spdlog/src
        PRIVATE vendor/imgui
        PRIVATE vendor/glad)

target_link_libraries(${PROJECT_NAME} glfw spdlog imgui glad)