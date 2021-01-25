set(SAMPLE_SOURCES
    triangle/Renderer.hpp)

set(SAMPLE_HEADERS
    triangle/Renderer.cpp
    main.cpp)

set(SAMPLE_SHADERS
    shaders/vertex.vs shaders/fragment.fs)

add_sample(00_triangle
    SOURCES ${SAMPLE_SOURCES} ${SAMPLE_HEADERS} ${SAMPLE_SHADERS}
    LINK glfw engine
    HEADER_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    DEFINITIONS SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders"
    )

