cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Bookstore2024)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Collect file

# Add the executable
add_executable(Bookstore2024
        main.cpp
        include/Directory.hpp
        include/MemoryRiver.hpp
        src/MemoryRiver.cpp
        src/Directory.cpp
        src/Unit.cpp
        include/Unit.hpp
)

# Link libraries
# target_link_libraries(Bookstore2024 <library_name>)