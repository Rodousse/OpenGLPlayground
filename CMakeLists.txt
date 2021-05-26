cmake_minimum_required(VERSION 3.11)

project(OpenGLPlayground
    VERSION 0.1.0
    DESCRIPTION "Realtime rendering sandbox applications"
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SCENE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/resources/scenes")
set(MATERIAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/resources/materials")
set(TEXTURE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/resources/textures")



include(GenerateExportHeader)
include(FetchContent)
include(cmake/UtilityFunctions.cmake)

# Path to use for cmake generated files
set(GENERATED_DIR "${CMAKE_BINARY_DIR}/generated")
message(STATUS "Generated files goes in : ${GENERATED_DIR}")
file(MAKE_DIRECTORY ${GENERATED_DIR})

if(NOT BUILD_SHARED_LIBS)
  set(GLEW_USE_STATIC_LIBS)
endif()

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Stbipp REQUIRED)
find_package(spdlog REQUIRED)
find_package(Assimp REQUIRED)
find_package(Eigen3 REQUIRED)
fetch_imgui_target()



add_subdirectory(src/engine)
add_subdirectory(src/app)
