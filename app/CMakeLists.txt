add_executable(${PROJECT_APP}
    main.cpp
)

target_include_directories(${PROJECT_APP} PUBLIC
                            ${CONAN_INCLUDE_DIRS} 
                            ${CMAKE_SOURCE_DIR}
                        )

target_link_libraries(${PROJECT_APP} PUBLIC ${PROJECT_LIB} ${CONAN_LIBS})
