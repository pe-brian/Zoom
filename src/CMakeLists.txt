#################################################################################
#
# Zoom C++ Library
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
 
set(SRCDIR ${ROOTDIR}/src)

set( 
    SOURCES
    ${SRCDIR}/Shape.cpp
    ${SRCDIR}/Kinetic.cpp
    ${SRCDIR}/Color.cpp
    ${SRCDIR}/Light.cpp
    ${SRCDIR}/Spot.cpp
    ${SRCDIR}/LightManager.cpp
)

add_library( 
  zoom
  SHARED
  ${SOURCES}
)

target_link_libraries(
  zoom
  ${ZOOST_LIBRARY}
  ${SFML_GRAPHICS_LIBRARY}
  ${SFML_WINDOW_LIBRARY}
  ${SFML_SYSTEM_LIBRARY}
)

install(
    TARGETS zoom
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
