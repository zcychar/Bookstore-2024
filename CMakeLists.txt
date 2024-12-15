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
        include/Storage/MemoryRiver.hpp
        src/Storage/MemoryRiver.cpp
        src/Directory.cpp
        src/Storage/Unit.cpp
        include/Storage/Unit.hpp
        include/Log.hpp
        src/Log.cpp
        include/Log.hpp
        src/User.cpp
        include/User.hpp
        src/Book.cpp
        include/Book.hpp
        include/Book.hpp
        src/User.cpp
        src/Utils.cpp
        include/Utils.hpp
)

# Link libraries
# target_link_libraries(Bookstore2024 <library_name>)