
set(EXAMPLE1 ${PROJECT_NAME}_example1)

add_executable(${EXAMPLE1}
    main.cpp
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_opengl2.cpp
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_glfw.h
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_opengl2.h
)

target_include_directories(${EXAMPLE1} PUBLIC
                            ${CONAN_INCLUDE_DIRS} 
                            ${CMAKE_SOURCE_DIR}
                            ${CMAKE_SOURCE_DIR}/bindings 
                        )

target_link_libraries(${EXAMPLE1} PUBLIC ${PROJECT_LIB} ${CONAN_LIBS})
