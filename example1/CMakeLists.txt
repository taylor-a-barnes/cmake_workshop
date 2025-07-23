cmake_minimum_required(VERSION 3.14)

# Project name and version
project(SimpleMPI VERSION 1.0
	          DESCRIPTION "Simple example of using MPI"
		  LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add the executable
add_executable(simplempi src/main.cpp)

# Find MPI
find_package(MPI REQUIRED)
target_link_libraries(simplempi PUBLIC MPI::MPI_CXX)

