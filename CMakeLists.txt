cmake_minimum_required(VERSION 3.27)

# 项目名称
project(toasted_renderer)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

include_directories(glm)

# 包含glad头文件
include_directories(glad/include)

# 包含glfw头文件
include_directories(/opt/homebrew/Cellar/glfw/3.4/include)
# 链接glfw库
link_directories(/opt/homebrew/Cellar/glfw/3.4/lib)

# 链接assimp库
include_directories(/opt/homebrew/Cellar/assimp/5.3.1/include)
link_directories(/opt/homebrew/Cellar/assimp/5.3.1/lib)

add_executable( ${PROJECT_NAME}
        main.cpp
        glad/src/glad.c

        src/thirdParty/stb_image.h
        src/thirdParty/stb_image.cpp

        src/shader.cpp
        src/path_helper.cpp
        src/camera.cpp
        src/camera.h
        src/utils/singleton.h
        src/Input.cpp
        src/render_window.cpp
        src/components/mesh.hpp
        src/components/material.hpp
        src/components/mesh_renderer.hpp
        src/components/model.cpp
        src/components/model.h
)

target_link_libraries(
        ${PROJECT_NAME}
        glfw
        assimp
)