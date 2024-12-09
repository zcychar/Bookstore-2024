cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Bookstore2024)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Collect file
aux_source_directory(src DIR_SRCS)
aux_source_directory(include DIR_INCLUDES)

# Add the executable
add_executable(Bookstore2024
        ${DIR_SRCS}
        ${DIR_INCLUDES}
        main.cpp
)

# Include directories
include_directories(include)

# Link libraries
# target_link_libraries(Bookstore2024 <library_name>)