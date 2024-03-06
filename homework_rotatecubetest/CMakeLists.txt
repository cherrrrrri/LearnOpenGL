# 设置CMake的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称定义
project(RotateCube)

# --- VCPKG集成开始 ---
# 设置vcpkg的工具链文件路径，这样CMake可以找到vcpkg提供的库和工具。
# 注意: 请确保以下路径正确地指向了您的vcpkg的工具链文件。
# 如果您和他人共享此CMakeLists.txt，请确保他们更新此路径以匹配其vcpkg安装。
set(CMAKE_TOOLCHAIN_FILE D:/vcpkg/scripts/buildsystems/vcpkg.cmake)

# 为find_package()设置路径，确保它可以找到vcpkg的包配置文件。
set(CMAKE_PREFIX_PATH D:/vcpkg/installed/x64-windows/share)

set(GLUT_glut_LIBRARY D:/vcpkg/installed/x64-windows/lib/freeglut.lib)

set(GLUT_INCLUDE_DIR D:/vcpkg/installed/x64-windows/include)

# --- VCPKG集成结束 ---
# 定义项目的可执行文件
add_executable(RotateCube main.cpp)


# 查找GLUT库
find_package(FreeGLUT CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE $<IF:$<TARGET_EXISTS:FreeGLUT::freeglut>,FreeGLUT::freeglut,FreeGLUT::freeglut_static>)