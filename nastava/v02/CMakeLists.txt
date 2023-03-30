# cmake_minimum_required(VERSION 3.17)

set(EXE v02)

add_executable(${EXE}
    shaderClass.h
    v02.cpp shaderClass.cpp VBO.h VBO.cpp EBO.h EBO.cpp)

set(SHADERS_FOLDER_V02 "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "shaders location")

configure_file (
                "pathconfig.h.in"
                "pathconfig.h"
                )

target_include_directories(${EXE} PRIVATE
        ${PROJECT_SOURCE_DIR}/third_party/glfw-3.3.2/include/
        ${PROJECT_SOURCE_DIR}/third_party/glm/
        ${PROJECT_SOURCE_DIR}/third_party/glew-2.1.0/include/
        ${PROJECT_SOURCE_DIR}/third_party/stb
        ${PROJECT_BINARY_DIR}
        ${PROJECT_BINARY_DIR}/nastava/v02/
        )

target_link_libraries(${EXE}
        ${OPENGL_LIBRARY}
        glfw
        GLEW_2100
        )
