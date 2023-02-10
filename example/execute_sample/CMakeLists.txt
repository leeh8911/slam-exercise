
set(EXAMPLE2 ${PROJECT_NAME}_example2)

add_executable(${EXAMPLE2}
    main.cpp
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_opengl2.cpp
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_glfw.h
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_opengl2.h
)

target_include_directories(${EXAMPLE2} PUBLIC
                            ${CONAN_INCLUDE_DIRS} 
                            ${CMAKE_SOURCE_DIR}
                        )

target_link_libraries(${EXAMPLE2} PUBLIC ${PROJECT_LIB} ${CONAN_LIBS})
