cmake_minimum_required(VERSION 3.5.0)
project(Tank CXX)

set(CMAKE_CXX_STANDARD 20)
set(MODULE_DIR ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_MODULE_PATH ${MODULE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)
set(EXTERNAL_LIBRARY_DIR ${CMAKE_BINARY_DIR}/lib)
set(EXTERNAL_LIBRARIES "")
set(EXTERNAL_INCLUDE_DIRS "")
set(EXTERNAL_DEPENDENCIES "")

# enable ccache
include(Cache)

include(FetchSFML)

include_directories(${INCLUDE_DIR})
include_directories(SYSTEM ${EXTERNAL_INCLUDE_DIRS})

file(GLOB_RECURSE PROJECT_SOURCE_FILES "${PROJECT_SOURCE_DIR}/${SOURCE_DIR}/*pp")

add_executable(Tank ${PROJECT_SOURCE_FILES})
target_link_libraries(Tank ${EXTERNAL_LIBRARIES})
add_dependencies(Tank ${EXTERNAL_DEPENDENCIES})
