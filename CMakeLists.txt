cmake_minimum_required(VERSION 3.11.3)

cmake_path(GET CMAKE_SOURCE_DIR FILENAME PROJECT_NAME)

project(${PROJECT_NAME} LANGUAGES CXX)

set(PROJECT_LIB ${PROJECT_NAME}_lib)
set(PROJECT_TEST ${PROJECT_NAME}_test)

set(CMAKE_CXX_STANDARD 20)

    
option(BUILD_APP "Build example" OFF)
option(BUILD_TEST "Build example" OFF)
option(BUILD_DOC "Build example" OFF)

set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH} 
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)

if(${BUILD_DOC})
add_subdirectory(docs)
endif()

if(${BUILD_TEST})
add_subdirectory(test)
endif()

if(${BUILD_APP})
    add_subdirectory(app)
endif()