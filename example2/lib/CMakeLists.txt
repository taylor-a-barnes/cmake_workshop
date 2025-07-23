cmake_minimum_required(VERSION 3.14)

set(MPIWRAPPER_USE_MPI "" CACHE STRING "Flag to use MPI (ON or OFF)")

# Project name and version
project(MPIWrapper VERSION 1.0.0
  DESCRIPTION "Wrapper for MPI libraries"
  LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add the library as a target
add_library(MPIWrapper)

# Create an alias for MPIWrapper, so that it can be referenced as MPIWrapper::MPIWrapper
# This is helpful to users, as it helps avoid potential namespace conflicts, and it makes it clear that MPIWrapper::MPIWrapper is a library
add_library(MPIWrapper::MPIWrapper ALIAS MPIWrapper)

# Add the library's source files
target_sources(MPIWrapper
  PRIVATE src/mpiwrapper.cpp)

set_target_properties(
  MPIWrapper
  PROPERTIES VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  #                   CXX_VISIBILITY_PRESET "hidden"
  #                   VISIBILITY_INLINES_HIDDEN TRUE
)

# Set the include directories for the library
# Generally, headers in src should only be visible within the library
# Headers meant to be visible to users should be in /include
target_include_directories(
  MPIWrapper
  PRIVATE src
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Generate an export header, and add it to the include directories
#include(GenerateExportHeader)
#generate_export_header(
#	MPIWrapper
#	EXPORT_FILE_NAME export/MPIWrapper/export_mpiwrapper.hpp
#)
#target_include_directories(
#	MPIWrapper
#	PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/export>
#	       $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDE}>
#)

# Find MPI
if ( MPIWRAPPER_USE_MPI STREQUAL "ON" )
  find_package(MPI REQUIRED)
elseif( MPIWRAPPER_USE_MPI STREQUAL "OFF" )
else()
  find_package(MPI)
endif()
if( MPI_FOUND )
  target_link_libraries(MPIWrapper PRIVATE MPI::MPI_CXX
  )
  target_compile_definitions(MPIWrapper PRIVATE __use_mpi=1)
else()
  message(WARNING "MPI was not found. Disabling MPI support.")
endif()

if (BUILD_SHARED_LIBS)
  set(MPIWrapper_STATIC_BUILD OFF)
else()
  set(MPIWrapper_STATIC_BUILD ON)
endif()
#message(WARNING "VALUE OF STATIC: ${MPIWrapper_STATIC_BUILD}")


##########################################################################
########################## BEGIN INSTALL SECTION #########################
##########################################################################

# Include the GNUInstallDirs module to get the canonical install paths defined
include(GNUInstallDirs)

# Set install locations
install(
  TARGETS MPIWrapper
  EXPORT MPIWrapperTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Explicitly install the header files
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
#install(
#	FILES "${CMAKE_CURRENT_BINARY_DIR}/export/MPIWrapper/export_mpiwrapper.hpp"
#	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/MPIWrapper
#)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "MPIWrapperConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

# message(WARNING "DATAROOT: ${CMAKE_INSTALL_DATAROOTDIR}"
configure_package_config_file(
  "${CMAKE_CURRENT_LIST_DIR}/cmake/MPIWrapperConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/MPIWrapperConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/MPIWrapper
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/MPIWrapperConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/MPIWrapperConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/MPIWrapper
)
install(
  EXPORT MPIWrapperTargets
  FILE MPIWrapperTargets.cmake
  NAMESPACE MPIWrapper::
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/MPIWrapper
)



