#################################################################################
#
# Zinetic C++ Library
# Copyright (c) 2011-2012 ZinTech
# 
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
# 
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 
# 3. This notice may not be removed or altered from any source distribution.
#
#################################################################################

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

# add an option for choosing the build type (shared or static)
set(BUILD_SHARED_LIBS TRUE CACHE BOOL "TRUE to build SFML as shared libraries, FALSE to build it as static libraries")

# add an option for building the examples
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
