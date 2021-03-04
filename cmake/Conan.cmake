macro(run_conan packages)
  # Download automatically, you can also just copy the conan.cmake file
  if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake"
                  TLS_VERIFY ON)
  endif()

  list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
  include(${CMAKE_BINARY_DIR}/conan.cmake)

  conan_add_remote(
    NAME
    bincrafters
    URL
    https://api.bintray.com/conan/bincrafters/public-conan)

  message(STATUS "DEPS: ${dependencies}")

  conan_cmake_configure(REQUIRES
                        ${packages}
                        GENERATORS
                        cmake_find_package)

  conan_cmake_autodetect(settings)
 
  conan_cmake_install(PATH_OR_REFERENCE .
                      BUILD missing
                      REMOTE conan-center
                      SETTINGS ${settings})

  endmacro()
