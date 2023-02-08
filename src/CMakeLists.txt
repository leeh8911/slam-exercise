file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_LIB} STATIC 
    ${SRC_FILES}
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_opengl2.cpp
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_glfw.h
    ${CMAKE_SOURCE_DIR}/bindings/imgui_impl_opengl2.h
    )

target_include_directories(${PROJECT_LIB} PUBLIC
                            ${CONAN_INCLUDE_DIRS}
                            ${CMAKE_SOURCE_DIR}
                            ${CMAKE_SOURCE_DIR}/bindings 
                        )

target_link_libraries(${PROJECT_LIB} PUBLIC
                        ${CONAN_LIBS}
                        )