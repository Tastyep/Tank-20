include(ExternalProject)

set(SFML_TARGET sfml)
set(SFML_VERSION 2.5.1)
set(SFML_ROOT_DIR ${EXTERNAL_LIBRARY_DIR}/sfml)
set(SFML_INSTALL_DIR ${SFML_ROOT_DIR}/install)
set(SFML_LIBRARIES audio graphics system window)

ExternalProject_Add(${SFML_TARGET}
  GIT_REPOSITORY    https://github.com/SFML/SFML.git 
  GIT_TAG           ${SFML_VERSION}
  PREFIX            ${SFML_ROOT_DIR}
  CMAKE_ARGS        -DCMAKE_INSTALL_PREFIX=${SFML_INSTALL_DIR}
)

list(APPEND EXTERNAL_DEPENDENCIES ${SFML_TARGET})
foreach(library ${SFML_LIBRARIES})
  list(APPEND EXTERNAL_LIBRARIES "${SFML_INSTALL_DIR}/lib/libsfml-${library}.so")
endforeach()
list(APPEND EXTERNAL_INCLUDE_DIRS ${SFML_INSTALL_DIR}/include)
