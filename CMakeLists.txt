cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Bookstore2024)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Collect file

# Add the executable
add_executable(code
        main.cpp
        include/Storage/MemoryRiver.hpp
        include/Storage/Unit.hpp

        include/Directory.hpp
        include/Log.hpp
        include/User.hpp
        include/Book.hpp
        include/Utils.hpp

        src/Log.cpp
        src/User.cpp
        src/Book.cpp
        src/Utils.cpp
)

# Link libraries
# target_link_libraries(Bookstore2024 <library_name>)