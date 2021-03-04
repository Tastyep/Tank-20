cmake_minimum_required(VERSION 3.10.0)
project(Tank CXX)

set(MODULE_DIR ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_MODULE_PATH ${MODULE_DIR})
include(StandardProjectSettings)
include(PreventInSourceBuilds)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)
set(EXTERNAL_LIBRARY_DIR ${CMAKE_BINARY_DIR}/lib)
set(EXTERNAL_LIBRARIES "")
set(EXTERNAL_INCLUDE_DIRS "")
set(EXTERNAL_DEPENDENCIES "")

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# Link this 'library' to set the compile time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

# enable ccache
include(Cache)

# set compiler flags
include(CompilerWarnings)
set_project_warnings(project_warnings)

# set sanitizer options if supported
include(Sanitizers)
enable_sanitizers(project_options)

# add the formatting target
include(Formatters)

# enable doxygen
include(Doxygen)
enable_doxygen()

# allow for static analysis options
include(StaticAnalyzers)

# Set up some extra Conan dependencies based on our needs before loading Conan
set(CONAN_PACKAGES
    "catch2/2.13.4
     docopt.cpp/0.6.3
     fmt/7.1.3
     spdlog/1.8.2
     sfml/2.5.1@bincrafters/stable
     imgui-sfml/2.1@bincrafters/stable
     ")

include(cmake/Conan.cmake)
run_conan(${CONAN_PACKAGES})

find_package(Catch2)
find_package(docopt)
find_package(fmt)
find_package(spdlog)
find_package(sfml)
find_package(ImGui-SFML)
list(
  APPEND
  EXTERNAL_LIBRARIES
  "Catch2::Catch2;docopt::docopt_s;fmt::fmt;spdlog::libspdlog;sfml::sfml;ImGui-SFML::ImGui-SFML"
)

include_directories(${INCLUDE_DIR})
include_directories(SYSTEM ${EXTERNAL_INCLUDE_DIRS})

file(GLOB_RECURSE PROJECT_SOURCE_FILES
     "${PROJECT_SOURCE_DIR}/${SOURCE_DIR}/*pp")
file(GLOB_RECURSE PROJECT_HEADER_FILES
     "${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}/*pp")
list(APPEND PROJECT_CODE_FILES ${PROJECT_SOURCE_FILES})
list(APPEND PROJECT_CODE_FILES ${PROJECT_HEADER_FILES})
add_format_target(${PROJECT_CODE_FILES})

add_executable(Tank ${PROJECT_SOURCE_FILES})
target_link_libraries(Tank PRIVATE project_warnings project_options
                                   ${EXTERNAL_LIBRARIES})
# add_dependencies(Tank ${EXTERNAL_DEPENDENCIES})
