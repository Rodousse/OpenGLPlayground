set(SAMPLE_SOURCES
    shadows/Data.hpp
    shadows/Renderer.hpp 
    shadows/LightRenderer.hpp 
    shadows/ShadowRenderer.hpp 
    )

set(SAMPLE_HEADERS
    shadows/Data.cpp
    shadows/Renderer.cpp
    shadows/LightRenderer.cpp 
    shadows/ShadowRenderer.cpp 
    main.cpp)

set(SAMPLE_SHADERS
    shaders/vertex.vs
    shaders/fragment.fs
    shaders/shadow.vs
    shaders/shadow.fs
    )

add_sample(06_shadows
    SOURCES ${SAMPLE_SOURCES} ${SAMPLE_HEADERS} ${SAMPLE_SHADERS}
    LINK glfw engine imgui 
    HEADER_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    DEFINITIONS
        -DSHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        -DMODEL_PATH="${SCENE_PATH}/sphereOnPlane2.fbx"
        ${IMGUI_COMPILE_FLAGS}
    )
