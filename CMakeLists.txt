# set the version of cmake
cmake_minimum_required(VERSION 2.8)

# set the rootdir
set(ROOTDIR ${CMAKE_SOURCE_DIR})

# specify the cmake configuration file
include(cmake/config.cmake)

# set the include directory
include_directories(
   ${ROOTDIR}/include
   ${ZOOST_INCLUDE_DIR}
   ${SFML_INCLUDE_DIR}
)

# set the compilation options
add_definitions(
   -Wfatal-errors
   -std=c++0x
   -DZOOM_EXPORTS
)

# add an option to choose the build type (shared or static)
set(BUILD_SHARED_LIBS TRUE CACHE BOOL "TRUE to build SFML as shared libraries, FALSE to build it as static libraries")

# add an option to build or not the examples
set(BUILD_EXAMPLES FALSE CACHE BOOL "TRUE to build the SFML examples, FALSE to ignore them")

# add the source files
add_subdirectory(src)

# add the examples files
if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

install( 
    DIRECTORY ./include/Zoom
    DESTINATION include
    COMPONENT devel
)
