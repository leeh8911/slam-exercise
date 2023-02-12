
set(APPLICATION ${PROJECT_NAME}_app)

add_executable(${APPLICATION}
    main.cpp
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_opengl2.cpp
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_glfw.h
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_opengl2.h
)

target_include_directories(${APPLICATION} PUBLIC
                            ${CONAN_INCLUDE_DIRS} 
                            ${CMAKE_SOURCE_DIR}
                        )

target_link_libraries(${APPLICATION} PUBLIC ${PROJECT_LIB} ${CONAN_LIBS})
