cmake_minimum_required(VERSION 3.27)

# 项目名称
project(toasted_renderer)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

include_directories(glm)

# 包含glad头文件
include_directories(glad/include)

# 包含glfw头文件
include_directories(/opt/homebrew/Cellar/glfw/3.4/lib)
# 链接glfw库
link_directories(/opt/homebrew/Cellar/glfw/3.4/lib)

add_executable( ${PROJECT_NAME}
        main.cpp
        glad/src/glad.c
        src/shader.cpp
        src/shader.h
)

target_link_libraries(
        ${PROJECT_NAME}
        glfw
)