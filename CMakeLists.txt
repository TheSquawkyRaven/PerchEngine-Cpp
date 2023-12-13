cmake_minimum_required(VERSION 3.10)

project(PerchEngine-Cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("${PROJECT_SOURCE_DIR}/SDL")
add_subdirectory(SDL)

message("-- Linking SDL --")

add_library(SDL2 SDL2.dll)

file(GLOB_RECURSE PerchEngine_SRC CONFIGURE_DEPENDS "PerchEngine-Cpp/*.h" "PerchEngine-Cpp/*.cpp" )
add_executable(PerchEngine ${PerchEngine_SRC})