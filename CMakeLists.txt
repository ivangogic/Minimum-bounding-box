cmake_minimum_required(VERSION 3.16)
project(Minimum_bounding_box)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(
        Minimum_bounding_box main.cpp
        utility/loadshaders.h
        utility/loadshaders.cpp
        utility/loadobj.h
        utility/loadobj.cpp
        utility/controls.h
        utility/controls.cpp
        convhull_3d.h
        libgdiam-1.0.3/gdiam.hpp
        libgdiam-1.0.3/gdiam.cpp
        mbb.h
        mbb.cpp)

target_compile_definitions(Minimum_bounding_box PRIVATE
    GLM_ENABLE_EXPERIMENTAL
)

if(APPLE)
    target_compile_definitions(Minimum_bounding_box PRIVATE
        GL_SILENCE_DEPRECATION
    )
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(Minimum_bounding_box PRIVATE
        /permissive-
        $<$<CONFIG:Release>:/O1>
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options(Minimum_bounding_box PRIVATE
        $<$<CONFIG:Release>:-O1>
    )
endif()

target_link_libraries(Minimum_bounding_box PRIVATE
    OpenGL::GL
    GLEW::GLEW
    glfw
    glm::glm
)
