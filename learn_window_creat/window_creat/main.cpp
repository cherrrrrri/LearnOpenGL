#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;
// 我们可以对窗口注册一个回调函数(Callback Function)，它会在每次窗口大小被调整的时候被调用。这个回调函数的原型如下
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
// glfwGetKey函数，它需要一个窗口以及一个按键作为输入。这个函数将会返回这个按键是否正在被按下
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


int main(int argc, char const* argv[])
{
    // 初始化的glfw;
    glfwInit();
    // 设置窗口的相关属性
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建对应的窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "learningGL", NULL, NULL);
    if (!window) {
        cout << "failed to create a window" << endl;
        // 销毁所有现在的窗口和光标
        glfwTerminate();
        return -1;
    }
    // 指定窗口的上下文（context）设为调用线程的当前上下文
    glfwMakeContextCurrent(window);
    // 告诉OpenGL渲染窗口的尺寸的大小
    // glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
    glViewport(0, 0, 800, 600);

    // 我们还需要注册这个函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数：
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // glfwWindowShouldClose函数在我们每次循环的开始前检查一次GLFW是否被要求退出
    // glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
    // glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        // glClearColor来设置清空屏幕所用的颜色
        glClearColor(1.0f, 0.5f, 0.3f, 1.0f);
        // glClear函数来清空屏幕的颜色缓冲，它接受一个缓冲位(Buffer Bit)来指定要清空的缓冲
        // 可能的缓冲位有GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}
