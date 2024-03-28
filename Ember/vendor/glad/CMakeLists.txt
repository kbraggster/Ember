cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)

project(Glad)

# Define the path to Glad header files
set(GLAD_HEADERS
        include/glad/glad.h
        include/KHR/khrplatform.h
)

# Define the path to Glad source files
set(GLAD_SOURCES src/glad.c)

# Create a library target for Glad
add_library(glad ${GLAD_HEADERS} ${GLAD_SOURCES})

# Set include directories for Glad
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
