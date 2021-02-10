set(SAMPLE_SOURCES
    ubo/Renderer.hpp )

set(SAMPLE_HEADERS
    ubo/Renderer.cpp
    main.cpp)

set(SAMPLE_SHADERS
    shaders/vertex.vs
    shaders/fragment.fs)

add_sample(03_ubo
    SOURCES ${SAMPLE_SOURCES} ${SAMPLE_HEADERS} ${SAMPLE_SHADERS}
    LINK glfw engine imgui
    HEADER_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    DEFINITIONS
        -DSHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        -DMODEL_PATH="${SCENE_PATH}/sphereOnPlane.fbx"
        ${IMGUI_COMPILE_FLAGS}
    )
