cmake_minimum_required(VERSION 3.20)
project(Baby_Photoshop)

set(CMAKE_CXX_STANDARD 20)

# Only include main.cpp and Filter.cpp to avoid multiple definitions
set(SOURCES
        src/Filter.cpp
)

# Create executable
add_executable(Baby_Photoshop ${SOURCES})

# Add include directories
target_include_directories(Baby_Photoshop PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/header
        ${CMAKE_CURRENT_SOURCE_DIR}/header/Image_Class
        ${CMAKE_CURRENT_SOURCE_DIR}/header/Winged_Dragon
)