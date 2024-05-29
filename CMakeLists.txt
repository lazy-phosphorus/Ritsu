# cmake requirement
cmake_minimum_required(VERSION 3.29.3)

# metadata
project(Ritsu VERSION 0.1.0 LANGUAGES C)

# third party dependency
find_package(PkgConfig REQUIRED)
pkg_search_module(Tesseract REQUIRED tesseract)
pkg_search_module(Lua REQUIRED lua)

# source code directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# header directory
include_directories(${SOURCE_DIR} ${Tesseract_INCLUDE_DIRS} ${Lua_INCLUDE_DIRS})

# collect source code
file(GLOB_RECURSE ALL_SOURCES ${SOURCE_DIR}/*.c)

# build target
add_executable(${PROJECT_NAME} ${ALL_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Tesseract_LIBRARIES} ${Lua_LIBRARIES})
