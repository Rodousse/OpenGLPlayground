

set(SAMPLE_NAME triangle)

set(SAMPLE_SOURCES
    triangle/Renderer.hpp )

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
#add_executable(00_triangle  ${SAMPLE_SOURCES} ${SAMPLE_HEADERS} ${SAMPLE_SHADERS})
#target_include_directories(00_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(00_triangle PRIVATE )
#target_compile_definitions(00_triangle PRIVATE SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders")

#math(EXPR SAMPLE_INDEX "${SAMPLE_INDEX}+1")
