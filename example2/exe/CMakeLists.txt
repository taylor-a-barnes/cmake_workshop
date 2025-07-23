cmake_minimum_required(VERSION 3.14)

# Project name and version
project(SimpleMPI VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED)

# Add the executable
add_executable(simplempi src/main.cpp)

# Link against the MPIWrapper library
find_package(MPIWrapper 1.0 REQUIRED)
target_link_libraries(simplempi PUBLIC MPIWrapper::MPIWrapper)
