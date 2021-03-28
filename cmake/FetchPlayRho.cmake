include(ExternalProject)

set(playrho_TARGET playrho)
set(playrho_VERSION v1.0.0)
set(playrho_ROOT_DIR ${EXTERNAL_LIBRARY_DIR}/${playrho_TARGET})
set(playrho_INSTALL_DIR ${playrho_ROOT_DIR}/install)

ExternalProject_Add(
  ${playrho_TARGET}
  GIT_REPOSITORY https://github.com/louis-langholtz/PlayRho.git
  GIT_TAG ${playrho_VERSION}
  PREFIX ${playrho_ROOT_DIR}
  CMAKE_ARGS -DPLAYRHO_INSTALL=ON -DCMAKE_INSTALL_PREFIX=${playrho_INSTALL_DIR})

set(playrho_INCLUDE_DIR ${playrho_INSTALL_DIR}/include)
set(playrho_LIBRARIES ${playrho_INSTALL_DIR}/lib/libPlayRho.a)
list(APPEND EXTERNAL_INCLUDE_DIRS ${playrho_INCLUDE_DIR})
list(APPEND EXTERNAL_LIBRARIES ${playrho_LIBRARIES})
list(APPEND EXTERNAL_DEPENDENCIES ${playrho_TARGET})
