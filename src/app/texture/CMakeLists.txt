
set(IMGUI_COMPILE_FLAGS
    -DIMGUI_INCLUDE_IMGUI_USER_H -DIMGUI_INCLUDE_IMGUI_USER_INL -DIMGUI_USE_GLEW -DIMGUI_USE_GLFW_BINDING)

set(SAMPLE_NAME texture)

set(SAMPLE_SOURCES
    texture/Renderer.hpp )

set(SAMPLE_HEADERS
    texture/Renderer.cpp
    main.cpp)

set(SAMPLE_SHADERS
    shaders/vertex.vs shaders/fragment.fs)

add_sample(01_texture
    SOURCES ${SAMPLE_SOURCES} ${SAMPLE_HEADERS} ${SAMPLE_SHADERS}
    LINK glfw engine Stbipp::Stbipp imgui
    HEADER_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    DEFINITIONS
        -DSHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        -DTEXTURE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/texture.jpg"
        -DTEXTURE2_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/texture2.jpg"
        ${IMGUI_COMPILE_FLAGS}
    )
