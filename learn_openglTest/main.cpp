#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
    // 初始化GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }
    // 创建窗口
    GLFWwindow *window = glfwCreateWindow(800, 600, "GLFW Window", NULL, NULL);//窗口对象，存放了窗口相关的信息
    if (!window)
    {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 将窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);

    // 初始化GLAD:用来管理openGL的函数指针
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return -1;
    }
    // 设置视口大小：可以比glfw的维度小
    glViewport(0, 0, 800, 600);//(参数左下角位置，渲染窗口的宽度和高度)

    // 设置窗口大小调整的回调
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height)
    { glViewport(0, 0, width, height); });
    
    // 主循环
    while (!glfwWindowShouldClose(window))
    {
        // 清空颜色缓冲
        glClearColor(0.0f, 0.0f, 0.3f, 1.0f);//设置清空屏幕用的颜色
        glClear(GL_COLOR_BUFFER_BIT);//清空上一次迭代渲染的结果
        // 处理GLFW事件：是否触发事件（键盘输入、鼠标移动），并更新窗口状态
        glfwPollEvents();
        // 交换缓冲
        glfwSwapBuffers(window);
    }

    // 终止GLFW
    glfwTerminate();//释放资源
    return 0;
}
