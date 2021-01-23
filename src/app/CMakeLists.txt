

set(APP_SOURCES
    main.cpp)

set(IMGUI_COMPILE_FLAGS
    "-DIMGUI_INCLUDE_IMGUI_USER_H -DIMGUI_INCLUDE_IMGUI_USER_INL -DIMGUI_USE_GLEW -DIMGUI_USE_GLFW_BINDING")


add_subdirectory(triangle)
add_subdirectory(texture)

add_executable(${PROJECT_NAME} ${APP_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw engine imgui)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    ${IMGUI_COMPILE_FLAGS})

message(STATUS ${WIN_DLL_LIST})

