file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE SRC_FILES_IMGUIS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/bindings/*.cpp)

add_library(${PROJECT_LIB} STATIC 
    ${SRC_FILES}
    ${SRC_FILES_IMGUIS}
    )

target_include_directories(${PROJECT_LIB} PUBLIC
                            ${CONAN_INCLUDE_DIRS}
                            ${CMAKE_SOURCE_DIR}
                            ${CMAKE_SOURCE_DIR}/bindings
                        )

target_link_libraries(${PROJECT_LIB} PUBLIC
                        ${CONAN_LIBS}
                        )