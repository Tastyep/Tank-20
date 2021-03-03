cmake_minimum_required(VERSION 3.5.0)
project(Tank CXX)

set(MODULE_DIR ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_MODULE_PATH ${MODULE_DIR})
include(PreventInSourceBuilds)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)
set(EXTERNAL_LIBRARY_DIR ${CMAKE_BINARY_DIR}/lib)
set(EXTERNAL_LIBRARIES "")
set(EXTERNAL_INCLUDE_DIRS "")
set(EXTERNAL_DEPENDENCIES "")

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# enable ccache
include(Cache)

# set compiler flags
include(CompilerWarnings)
set_project_warnings(project_warnings)
include(FetchSFML)

include_directories(${INCLUDE_DIR})
include_directories(SYSTEM ${EXTERNAL_INCLUDE_DIRS})
 
file(GLOB_RECURSE PROJECT_SOURCE_FILES "${PROJECT_SOURCE_DIR}/${SOURCE_DIR}/*pp")
 
add_executable(Tank ${PROJECT_SOURCE_FILES})
target_link_libraries(Tank project_warnings ${EXTERNAL_LIBRARIES})
add_dependencies(Tank ${EXTERNAL_DEPENDENCIES})
