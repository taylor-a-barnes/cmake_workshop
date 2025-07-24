# Build Instructions

```
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build build
```

# Enabling the Library to Compile With CMake

Create the following `CMakeLists.txt`:

```
cmake_minimum_required(VERSION 3.14) 

set(MPIWrapper_USE_MPI "DEFAULT" CACHE STRING
  "String to indicate whether to use MPI (ON, OFF, or DEFAULT)")

project(MPIWrapper VERSION 1.0.0
  DESCRIPTION "Wrapper for MPI libraries"
  LANGUAGES CXX)

# Add the library
add_library(MPIWrapper)

# Create an alias for the library
add_library(MPIWrapper::MPIWrapper ALIAS MPIWrapper)

# Add the library's source files
target_sources(MPIWrapper
  PRIVATE src/mpiwrapper.cpp)

# Specify the C++ standard
target_compile_features(MPIWrapper PUBLIC cxx_std_11)

set_target_properties(MPIWrapper
  PROPERTIES VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR})

# Set the include directories
target_include_directories(
  MPIWrapper
  PRIVATE src
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Find MPI
if ( MPIWrapper_USE_MPI STREQUAL "ON" )
  find_package(MPI REQUIRED)
elseif( MPIWrapper_USE_MPI STREQUAL "OFF" )
elseif( MPIWrapper_USE_MPI STREQUAL "DEFAULT" )
  find_package(MPI)
else()
  message(FATAL_ERROR "Unrecognized value of MPIWrapper_USE_MPI")
endif()
if ( MPI_FOUND )
  target_link_libraries(MPIWrapper PUBLIC MPI::MPI_CXX)
  target_compile_definitions(MPIWrapper PUBLIC __use_mpi=1)
else()
  message(WARNING "MPI was not found. Disabling MPI support.")
endif()
```

Now compile with

```
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build build
```

This should produce `libMPIWrapper.a`.


# Making the Library Installable

Append the following to your `CMakeLists.txt`:

```
######################################################
# BEGIN INSTALL SECTION
######################################################

include(GNUInstallDirs)

# Set install locations
install(TARGETS MPIWrapper
        EXPORT MPIWrapperTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
```

Now compile and install with

```
rm -rf build
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build build
cmake --install build
```

This produces:

```
root@791f42c36642:/work/example2/lib# cmake --install build
-- Install configuration: ""
-- Installing: /usr/local/lib/libMPIWrapper.a
```


Append the following line:

```
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
```

Now compile and install with

```
rm -rf build
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build build
cmake --install build
```


```
root@791f42c36642:/work/example2/lib# cmake --install build
-- Install configuration: ""
-- Installing: /usr/local/lib/libMPIWrapper.a
-- Up-to-date: /usr/local/include
-- Installing: /usr/local/include/mpiwrapper.h
```

Let's try using the library in our executable:

```
cd ../exe
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
```

```
CMake Error at CMakeLists.txt:13 (find_package):
  By not providing "FindMPIWrapper.cmake" in CMAKE_MODULE_PATH this project
  has asked CMake to find a package configuration file provided by
  "MPIWrapper", but CMake did not find one.

  Could not find a package configuration file provided by "MPIWrapper"
  (requested version 1.0) with any of the following names:

    MPIWrapperConfig.cmake
    mpiwrapper-config.cmake

  Add the installation prefix of "MPIWrapper" to CMAKE_PREFIX_PATH or set
  "MPIWrapper_DIR" to a directory containing one of the above files.  If
  "MPIWrapper" provides a separate development package or SDK, be sure it has
  been installed.
```


# Setting up a CMake Package Configuration

Add the following to the end of the library's `CMakeLists.txt`:

```
# Create the CMake configuration files
include(CMakePackageConfigHelpers)
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/MPIWrapperConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/MPIWrapperConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/MPIWrapper)
```

Now create a file `cmake/MPIWrapperConfig.cmake.in`, and add to it:

```
@PACKAGE_INIT@

include(CMakeFindDependencyMacro)
find_dependency(MPI)

check_required_components("@PROJECT_NAME@")
```

```
rm -rf build
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build build
```

This creats a new file at `build/MPIWrapperConfig.cmake`.  View it now.

```
cmake --install install
```



