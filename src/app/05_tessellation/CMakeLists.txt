set(SAMPLE_SOURCES
    tessellation/Renderer.hpp )

set(SAMPLE_HEADERS
    tessellation/Renderer.cpp
    main.cpp)

set(SAMPLE_SHADERS
    shaders/vertex.vs
    shaders/fragment.fs
    shaders/tesEval.tese
    shaders/tesControl.tesc
    )

add_sample(05_tessellation
    SOURCES ${SAMPLE_SOURCES} ${SAMPLE_HEADERS} ${SAMPLE_SHADERS}
    LINK glfw engine imgui Stbipp::Stbipp
    HEADER_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    DEFINITIONS
        -DSHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        -DMODEL_PATH="${SCENE_PATH}/sphereOnPlane2.fbx"
        -DMATERIAL_PATH="${MATERIAL_PATH}/stone"
        ${IMGUI_COMPILE_FLAGS}
    )
