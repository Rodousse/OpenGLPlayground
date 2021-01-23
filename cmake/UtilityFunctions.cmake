

function(fetch_imgui_target)
    FetchContent_Declare(
      imguirep
      GIT_REPOSITORY https://github.com/Flix01/imgui.git
      GIT_TAG        1355f81
    )

    FetchContent_GetProperties(imguirep)
    if(NOT imguirep_POPULATED)
      FetchContent_Populate(imguirep)
      set(imgui_SRC
          ${imguirep_SOURCE_DIR}/imgui.cpp
          ${imguirep_SOURCE_DIR}/imgui_demo.cpp
          ${imguirep_SOURCE_DIR}/imgui_draw.cpp
          ${imguirep_SOURCE_DIR}/imgui_widgets.cpp
          ${imguirep_SOURCE_DIR}/addons/imguifilesystem/imguifilesystem.cpp
          ${imguirep_SOURCE_DIR}/examples/imgui_impl_glfw.cpp
          ${imguirep_SOURCE_DIR}/examples/imgui_impl_opengl3.cpp)
      add_library(imgui ${imgui_SRC})
      target_include_directories(imgui PUBLIC ${imguirep_SOURCE_DIR} ${imguirep_SOURCE_DIR}/examples ${imguirep_SOURCE_DIR}/addons/imguifilesystem)
      target_link_libraries(imgui PRIVATE glfw GLEW::GLEW OpenGL::GL)
    endif()
    message(STATUS ${imguirep_SOURCE_DIR})
    message(STATUS  ${imgui_file_dialog_SOURCE_DIR})


endfunction()



function(add_sample NAME)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs SOURCES LINK HEADER_DIRS DEFINITIONS)
    cmake_parse_arguments(SAMPLEARGS "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN} )
    message(STATUS "Creating target : ${NAME}")
    add_executable(${NAME} ${SAMPLEARGS_SOURCES})
    target_link_libraries(${NAME} PRIVATE ${SAMPLEARGS_LINK})
    target_include_directories(${NAME} PRIVATE ${SAMPLEARGS_HEADER_DIRS})
    target_compile_definitions(${NAME} PRIVATE ${SAMPLEARGS_DEFINITIONS})

endfunction()