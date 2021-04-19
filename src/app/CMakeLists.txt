
set(IMGUI_COMPILE_FLAGS
    "-DIMGUI_INCLUDE_IMGUI_USER_H -DIMGUI_INCLUDE_IMGUI_USER_INL -DIMGUI_USE_GLEW -DIMGUI_USE_GLFW_BINDING")

add_subdirectory(00_triangle)
add_subdirectory(01_texture)
add_subdirectory(02_3d_model)
add_subdirectory(03_ubo)
add_subdirectory(04_fbo)

message(STATUS ${WIN_DLL_LIST})

