set(ENGINE_SRC
    engine/Camera.cpp
    engine/DataIO.cpp
    engine/GLErrorHandling.cpp
    engine/GLProgram.cpp
    engine/GLShader.cpp
    engine/GLTexture.cpp
    engine/Mesh.cpp
    engine/PerspectiveCamera.cpp
    )

set(ENGINE_HEADERS
    engine/Camera.hpp
    engine/CommonTypes.hpp
    engine/DataIO.hpp
    engine/GLErrorHandling.hpp
    engine/GLObject.hpp
    engine/GLProgram.hpp
    engine/GLShader.hpp
    engine/GLTexture.hpp
    engine/Mesh.hpp
    engine/PerspectiveCamera.hpp
    engine/Scene.hpp
    )


add_library(engine ${ENGINE_SRC} ${ENGINE_HEADERS})

generate_export_header(engine
  EXPORT_MACRO_NAME ENGINE_API
  EXPORT_FILE_NAME ${GENERATED_DIR}/EngineSymbols.h
)

set(ENGINE_STATIC_FLAG "ENGINE_STATIC_DEFINE")
if(BUILD_SHARED_LIBS)
    set(ENGINE_STATIC_FLAG "")
endif()
target_include_directories(engine
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${GENERATED_DIR}>)
target_link_libraries(engine PUBLIC Eigen3::Eigen spdlog::spdlog_header_only GLEW::GLEW OpenGL::GL PRIVATE assimp::assimp)
target_compile_definitions(engine PUBLIC ${ENGINE_STATIC_FLAG} _USE_MATH_DEFINES _ENABLE_EXTENDED_ALIGNED_STORAGE PRIVATE ENGINE_EXPORT)

