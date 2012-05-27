# define the ZOOST_STATIC macro if static build was chosen
if(ZOOST_STATIC_LIBRARIES)
    add_definitions(-DZOOST_STATIC)
endif()

# deduce the libraries suffix from the options
set(FIND_ZOOST_LIB_SUFFIX "")
if(ZOOST_STATIC_LIBRARIES)
    set(FIND_ZOOST_LIB_SUFFIX "${FIND_ZOOST_LIB_SUFFIX}-s")
    set(ZOOST_LIBNAME "zoost-s")
else()
    set(ZOOST_LIBNAME "zoost")
endif()

# find the ZOOST include directory
find_path(ZOOST_INCLUDE_DIR Zoost/Config.hpp
          PATH_SUFFIXES include
          PATHS
          ~/Library/Frameworks
          /Library/Frameworks
          /usr/local/
          /usr/
          /sw          # Fink
          /opt/local/  # DarwinPorts
          /opt/csw/    # Blastwave
          /opt/
          ${ZOOSTDIR}
          $ENV{ZOOSTDIR})

# check the version number
set(ZOOST_VERSION_OK TRUE)
if(ZOOST_FIND_VERSION AND ZOOST_INCLUDE_DIR)
    # extract the major and minor version numbers from ZOOST/Config.hpp
    FILE(READ "${ZOOST_INCLUDE_DIR}/ZOOST/Config.hpp" ZOOST_CONFIG_HPP_CONTENTS)
    STRING(REGEX MATCH ".*#define ZOOST_VERSION_MAJOR ([0-9]+).*#define ZOOST_VERSION_MINOR ([0-9]+).*" ZOOST_CONFIG_HPP_CONTENTS "${ZOOST_CONFIG_HPP_CONTENTS}")
    STRING(REGEX REPLACE ".*#define ZOOST_VERSION_MAJOR ([0-9]+).*" "\\1" ZOOST_VERSION_MAJOR "${ZOOST_CONFIG_HPP_CONTENTS}")
    STRING(REGEX REPLACE ".*#define ZOOST_VERSION_MINOR ([0-9]+).*" "\\1" ZOOST_VERSION_MINOR "${ZOOST_CONFIG_HPP_CONTENTS}")
    math(EXPR ZOOST_REQUESTED_VERSION "${ZOOST_FIND_VERSION_MAJOR} * 10 + ${ZOOST_FIND_VERSION_MINOR}")

    # if we could extract them, compare with the requested version number
    if (ZOOST_VERSION_MAJOR)
        # transform version numbers to an integer
        math(EXPR ZOOST_VERSION "${ZOOST_VERSION_MAJOR} * 10 + ${ZOOST_VERSION_MINOR}")

        # compare them
        if(ZOOST_VERSION LESS ZOOST_REQUESTED_VERSION)
            set(ZOOST_VERSION_OK FALSE)
        endif()
    else()
        # ZOOST version is < 2.0
        if (ZOOST_REQUESTED_VERSION GREATER 19)
            set(ZOOST_VERSION_OK FALSE)
            set(ZOOST_VERSION_MAJOR 1)
            set(ZOOST_VERSION_MINOR x)
        endif()
    endif()
endif()

# find the requested modules
set(ZOOST_FOUND TRUE) # will be set to false if one of the required modules is not found
set(FIND_ZOOST_LIB_PATHS ~/Library/Frameworks
                        /Library/Frameworks
                        /usr/local
                        /usr
                        /sw
                        /opt/local
                        /opt/csw
                        /opt
                        ${ZOOSTDIR}
                        $ENV{ZOOSTDIR})

# debug library
find_library(ZOOST_LIBRARY_DEBUG
         NAMES ${ZOOST_LIBNAME}-d
         PATH_SUFFIXES lib64 lib
         PATHS ${FIND_ZOOST_LIB_PATHS})

# release library
find_library(ZOOST_LIBRARY_RELEASE
         NAMES ${ZOOST_LIBNAME}
         PATH_SUFFIXES lib64 lib
         PATHS ${FIND_ZOOST_LIB_PATHS})

if (ZOOST_LIBRARY_DEBUG OR ZOOST_LIBRARY_RELEASE)
# library found
set(ZOOST_FOUND TRUE)

# if both are found, set ZOOST_XXX_LIBRARY to contain both
if (ZOOST_LIBRARY_DEBUG AND ZOOST_LIBRARY_RELEASE)
    set(ZOOST_LIBRARY debug     ${ZOOST_LIBRARY_DEBUG}
                      optimized ${ZOOST_LIBRARY_RELEASE})
endif()

# if only one debug/release variant is found, set the other to be equal to the found one
if (ZOOST_LIBRARY_DEBUG AND NOT ZOOST_LIBRARY_RELEASE)
    # debug and not release
    set(ZOOST_LIBRARY_RELEASE ${ZOOST_LIBRARY_DEBUG})
    set(ZOOST_LIBRARY         ${ZOOST_LIBRARY_DEBUG})
endif()
if (ZOOST_LIBRARY_RELEASE AND NOT ZOOST_LIBRARY_DEBUG)
    # release and not debug
    set(ZOOST_LIBRARY_DEBUG ${ZOOST_LIBRARY_RELEASE})
    set(ZOOST_LIBRARY       ${ZOOST_LIBRARY_RELEASE})
endif()
else()
# library not found
set(ZOOST_FOUND FALSE)
endif()

# mark as advanced
MARK_AS_ADVANCED(ZOOST_LIBRARY
             ZOOST_LIBRARY_RELEASE
             ZOOST_LIBRARY_DEBUG)

# add to the global list of libraries
set(ZOOST_LIBRARIES ${ZOOST_LIBRARIES} "${ZOOST_${FIND_ZOOST_COMPONENT_UPPER}_LIBRARY}")

# handle errors
if(NOT ZOOST_VERSION_OK)
    # ZOOST version not ok
    set(FIND_ZOOST_ERROR "ZOOST found but version too low (requested: ${ZOOST_FIND_VERSION}, found: ${ZOOST_VERSION_MAJOR}.${ZOOST_VERSION_MINOR})")
    set(ZOOST_FOUND FALSE)
elseif(NOT ZOOST_FOUND)
    # include directory or library not found
    set(FIND_ZOOST_ERROR "Could NOT find ZOOST (missing: ${FIND_ZOOST_MISSING})")
endif()
if (NOT ZOOST_FOUND)
    if(ZOOST_FIND_REQUIRED)
        # fatal error
        message(FATAL_ERROR ${FIND_ZOOST_ERROR})
    elseif(NOT ZOOST_FIND_QUIETLY)
        # error but continue
        message("${FIND_ZOOST_ERROR}")
    endif()
endif()

# handle success
if(ZOOST_FOUND)
    message("Found ZOOST: ${ZOOST_INCLUDE_DIR}")
endif()
