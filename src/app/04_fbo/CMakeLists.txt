set(SAMPLE_SOURCES
    fbo/Renderer.hpp 
    fbo/ShadingRenderer.hpp
    fbo/GRenderer.hpp
    fbo/Types.hpp
    )

set(SAMPLE_HEADERS
    fbo/Renderer.cpp
    fbo/ShadingRenderer.cpp
    fbo/GRenderer.cpp
    fbo/Types.cpp
    main.cpp
    )

set(SAMPLE_SHADERS
    shaders/gbuffer.vs
    shaders/gbuffer.fs
    shaders/shading.vs
    shaders/shading.fs)

add_sample(04_fbo
    SOURCES ${SAMPLE_SOURCES} ${SAMPLE_HEADERS} ${SAMPLE_SHADERS}
    LINK glfw engine imgui
    HEADER_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    DEFINITIONS
        -DSHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        -DMODEL_PATH="${SCENE_PATH}/sphereOnPlane.fbx"
        ${IMGUI_COMPILE_FLAGS}
    )
