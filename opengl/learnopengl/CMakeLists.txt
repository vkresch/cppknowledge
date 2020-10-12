cmake_minimum_required(VERSION 3.8.0)
set(CMAKE_CXX_FLAGS "-std=c++11")
project (OpenglTut)

# Add glm
add_subdirectory(libs/glm/glm)

# Add glfw
add_subdirectory(libs/glfw)
include_directories(libs/glfw/include)

# Add glad
add_subdirectory(libs/glad)

set(SOURCE_FILES main.cpp)

# Create the main executable
add_executable(main ${SOURCE_FILES})

#GLFW additions
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Link glm
target_link_libraries(main glm)

# Link glad
target_link_libraries(main glad)

# Link glfw
target_link_libraries(main glfw ${GLFW_LIBRARIES})

# Add compile options
target_compile_options(main PRIVATE -Wall -Wextra -pedantic)