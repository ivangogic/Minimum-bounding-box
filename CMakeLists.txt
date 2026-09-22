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

add_library(mbb_core STATIC
    mbb.cpp
    mbb.h
    convhull_3d.h
    libgdiam-1.0.3/gdiam.hpp
    libgdiam-1.0.3/gdiam.cpp
)

target_include_directories(mbb_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(mbb_core PRIVATE
        /permissive-
        $<$<CONFIG:Release>:/O1>
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options(mbb_core PRIVATE
        $<$<CONFIG:Release>:-O1>
    )
endif()

add_executable(Minimum_bounding_box
    main.cpp
    utility/loadshaders.h
    utility/loadshaders.cpp
    utility/loadobj.h
    utility/loadobj.cpp
    utility/controls.h
    utility/controls.cpp
)

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
    mbb_core
    OpenGL::GL
    GLEW::GLEW
    glfw
    glm::glm
)

include(CTest)

if(BUILD_TESTING)
    add_executable(mbb_volume_regression_test
        tests/mbb_volume_regression_test.cpp
    )
    set_target_properties(mbb_volume_regression_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
    target_link_libraries(mbb_volume_regression_test PRIVATE mbb_core)
    add_test(
        NAME mbb_volume_regression_test
        COMMAND mbb_volume_regression_test ${CMAKE_CURRENT_SOURCE_DIR}/tetrahedron.obj
    )
endif()
