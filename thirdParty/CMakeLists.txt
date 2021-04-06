cmake_minimum_required(VERSION 3.8)


project(playground_dep LANGUAGES C CXX)

option(BUILD_SHARED_LIBS "Build as shared libraries" ON)
option(BUILD_ASSIMP "Build the library assimp" ON)
option(BUILD_EIGEN "Build the library eigen" ON)
option(BUILD_STBIPP "Build the library STBIPP" ON)
option(BUILD_GLFW "Build the library GLFW" ON)
option(BUILD_GLEW_CMAKE "Build the library GLEW-CMake" ON)
option(BUILD_SPDLOG "Build the library spdlog" ON)

include (ExternalProject)

set(CMAKE_GENERIC_OPTIONS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS})

if(BUILD_ASSIMP)
    ExternalProject_Add(assimp
        GIT_REPOSITORY "https://github.com/assimp/assimp.git"
        GIT_TAG "3e5feb4"
        BUILD_IN_SOURCE 0
        INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
        CMAKE_ARGS ${CMAKE_GENERIC_OPTIONS} -DASSIMP_INSTALL_PDB=FALSE  -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DASSIMP_BUILD_TESTS=OFF
        )
endif()

if(BUILD_EIGEN)
    ExternalProject_Add(eigen
        GIT_REPOSITORY "https://gitlab.com/libeigen/eigen.git"
        GIT_TAG "3.3.7"
        BUILD_IN_SOURCE 0
        INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        )
endif()

if(BUILD_STBIPP)
    ExternalProject_Add(stbipp
        GIT_REPOSITORY "https://github.com/Rodousse/stbipp.git"
        GIT_TAG "origin/develop"
        BUILD_IN_SOURCE 0
        INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
        CMAKE_ARGS  ${CMAKE_GENERIC_OPTIONS} -DSTBIPP_BUILD_EXAMPLE=OFF
        )

endif()

if(BUILD_GLFW)
    ExternalProject_Add(glfw
        GIT_REPOSITORY "https://github.com/glfw/glfw.git"
        GIT_TAG "3.3.2"
        BUILD_IN_SOURCE 0
        INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
        CMAKE_ARGS ${CMAKE_GENERIC_OPTIONS} -DGLFW_BUILD_DOCS=OFF
        )
endif()

if(BUILD_GLEW_CMAKE)

    set(GLEW_BUILD_STATIC TRUE)
    if(BUILD_SHARED_LIBS)
        set(GLEW_BUILD_STATIC FALSE)
    endif()
    ExternalProject_Add(glew-cmake
        GIT_REPOSITORY "https://github.com/Perlmint/glew-cmake.git"
        GIT_TAG "glew-cmake-2.2.0"
        BUILD_IN_SOURCE 0
        INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
        CMAKE_ARGS ${CMAKE_GENERIC_OPTIONS} -Dglew-cmake_BUILD_SHARED=${BUILD_SHARED_LIBS} -Dglew-cmake_BUILD_STATIC=${GLEW_BUILD_STATIC} -DONLY_LIBS=ON
        )
endif()

if(BUILD_SPDLOG)

    ExternalProject_Add(spdlog
        GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
        GIT_TAG "v1.8.2"
        BUILD_IN_SOURCE 0
        INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
        CMAKE_ARGS ${CMAKE_GENERIC_OPTIONS} -DSPDLOG_BUILD_SHARED=${BUILD_SHARED_LIBS} -DSPDLOG_BUILD_EXAMPLE=OFF -DSPDLOG_INSTALL=ON
        )
endif()
