#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;
// ���ǿ��ԶԴ���ע��һ���ص�����(Callback Function)��������ÿ�δ��ڴ�С��������ʱ�򱻵��á�����ص�������ԭ������
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
// glfwGetKey����������Ҫһ�������Լ�һ��������Ϊ���롣����������᷵����������Ƿ����ڱ�����
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


int main(int argc, char const* argv[])
{
    // ��ʼ����glfw;
    glfwInit();
    // ���ô��ڵ��������
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ������Ӧ�Ĵ���
    GLFWwindow* window = glfwCreateWindow(800, 600, "learningGL", NULL, NULL);
    if (!window) {
        cout << "failed to create a window" << endl;
        // �����������ڵĴ��ں͹��
        glfwTerminate();
        return -1;
    }
    // ָ�����ڵ������ģ�context����Ϊ�����̵߳ĵ�ǰ������
    glfwMakeContextCurrent(window);
    // ����OpenGL��Ⱦ���ڵĳߴ�Ĵ�С
    // glViewport����ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ���
    glViewport(0, 0, 800, 600);

    // ���ǻ���Ҫע���������������GLFW����ϣ��ÿ�����ڵ�����С��ʱ��������������
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // glfwWindowShouldClose����������ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�
    // glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
    // glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ��
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        // glClearColor�����������Ļ���õ���ɫ
        glClearColor(1.0f, 0.5f, 0.3f, 1.0f);
        // glClear�����������Ļ����ɫ���壬������һ������λ(Buffer Bit)��ָ��Ҫ��յĻ���
        // ���ܵĻ���λ��GL_COLOR_BUFFER_BIT��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}
