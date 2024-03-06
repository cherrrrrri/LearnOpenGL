cmake_minimum_required(VERSION 3.16)
project(yaml_lerning)

# 如果您和他人共享此CMakeLists.txt，请确保他们更新此路径以匹配其vcpkg安装。
set(CMAKE_TOOLCHAIN_FILE D:/vcpkg/scripts/buildsystems/vcpkg.cmake)

# 为find_package()设置路径，确保它可以找到vcpkg的包配置文件。
set(CMAKE_PREFIX_PATH D:/vcpkg/installed/x64-windows/share)

set(CMAKE_CXX_STANDARD 11)

add_executable(yaml_lerning main.cpp)

# 寻找并链接yaml
find_package(yaml-cpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}  PRIVATE yaml-cpp::yaml-cpp)