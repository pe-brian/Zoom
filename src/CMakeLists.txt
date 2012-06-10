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
