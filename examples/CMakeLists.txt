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

add_executable( 
  example1
  example1.cpp
)

add_executable( 
  example2
  example2.cpp
)

add_executable( 
  example3
  example3.cpp
)

include_directories(
   ${ZOOST_INCLUDE_DIR}
   ${ZOOM_INCLUDE_DIR}
   ${SFML_INCLUDE_DIR}
)

target_link_libraries(
  example1
  zoom
  ${ZOOST_LIBRARY}
  ${SFML_GRAPHICS_LIBRARY}
  ${SFML_WINDOW_LIBRARY}
  ${SFML_SYSTEM_LIBRARY}
)

target_link_libraries(
  example2
  zoom
  ${ZOOST_LIBRARY}
  ${SFML_GRAPHICS_LIBRARY}
  ${SFML_WINDOW_LIBRARY}
  ${SFML_SYSTEM_LIBRARY}
)

target_link_libraries(
  example3
  zoom
  ${ZOOST_LIBRARY}
  ${SFML_GRAPHICS_LIBRARY}
  ${SFML_WINDOW_LIBRARY}
  ${SFML_SYSTEM_LIBRARY}
)