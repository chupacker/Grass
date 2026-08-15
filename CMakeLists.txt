cmake_minimum_required(VERSION 3.15...4.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(
        grass
        VERSION 1.0
        LANGUAGES CXX C
)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)

add_executable(grass
        src/main.cpp
		vendor/glad/src/gl.c
        src/utils/Buffers.h
        src/utils/Buffers.cpp
        src/utils/Shader.h
        src/utils/Shader.cpp
        src/utils/Utils.h
        src/utils/Utils.cpp
        src/utils/Window.h
        src/utils/Window.cpp
        src/utils/App.cpp
        src/utils/App.h
		src/utils/Camera.cpp
		src/utils/Camera.h
		src/utils/Skybox.cpp
		src/utils/Skybox.h
		src/utils/stb_image.h
)

set_target_properties(grass PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        COMPILE_WARNING_AS_ERROR ON
)
target_compile_options(grass PRIVATE -Wall -Wextra -pedantic)

target_include_directories(grass PRIVATE
        vendor/glfw/include
        vendor/glad/include
)

target_link_libraries(grass PRIVATE
        glfw
        glm
)
