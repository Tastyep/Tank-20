include(ExternalProject)

set(tmxlite_TARGET tmxlite)
set(tmxlite_VERSION v1.2.1)
set(tmxlite_ROOT_DIR ${EXTERNAL_LIBRARY_DIR}/${tmxlite_TARGET})
set(tmxlite_INSTALL_DIR ${tmxlite_ROOT_DIR}/install)

ExternalProject_Add(
  ${tmxlite_TARGET}
  GIT_REPOSITORY https://github.com/fallahn/tmxlite.git
  GIT_TAG ${tmxlite_VERSION}
  PREFIX ${tmxlite_ROOT_DIR}
  SOURCE_SUBDIR ${tmxlite_TARGET} # The CMakelists file is in that subdirectory
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${tmxlite_INSTALL_DIR})

set(tmxlite_INCLUDE_DIR ${tmxlite_INSTALL_DIR}/include)
set(tmxlite_LIBRARIES ${tmxlite_INSTALL_DIR}/lib/libtmxlite.so)
list(APPEND EXTERNAL_INCLUDE_DIRS ${tmxlite_INCLUDE_DIR})
list(APPEND EXTERNAL_LIBRARIES ${tmxlite_LIBRARIES})
list(APPEND EXTERNAL_DEPENDENCIES ${tmxlite_TARGET})
