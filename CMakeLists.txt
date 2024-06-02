# WARNING: Do not run "cmake <dir>" directly.
# WARNING: Please use presets.

# Example: "cmake <dir> --preset <name>"

# cmake requirement
cmake_minimum_required(VERSION 3.29.3)

# project metadata
project(ritsu VERSION 0.1.0 LANGUAGES C)

# third party dependency
find_package(PkgConfig REQUIRED)
pkg_search_module(TESSERACT REQUIRED tesseract)

# header directory`
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src ${TESSERACT_INCLUDE_DIRS})

# source code
file(GLOB_RECURSE ALL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

# build target
add_executable(${PROJECT_NAME} ${ALL_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${TESSERACT_LIBRARIES})
