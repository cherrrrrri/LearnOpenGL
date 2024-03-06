#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//顶点着色器源码
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";


//片段着色器源码
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main(){
    // glfw初始化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw创建窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GreenTriangle", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //顶点着色器绑定
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建着色器
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);//把源码附加到着色器上
    glCompileShader(vertexShader);//编译着色器

    //监测着色器的编译有没有错
    int success;//是否成功编译
    char infoLog[512];//储存错误信息
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);//检查是否编译成功
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }

    //片段着色器绑定
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }

    //着色器程序对象
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();//创建着色器对象
    glAttachShader(shaderProgram,vertexShader);//把顶点着色器附加到程序对象上
    glAttachShader(shaderProgram,fragmentShader);//把片段着色器附加到程序对象上
    glLinkProgram(shaderProgram);//链接

    //检验链接着色器是否失败
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout << "ERROR::LINK_FAILED\n" << infoLog << endl;
    }
    glDeleteShader(vertexShader);//删除顶点着色器
    glDeleteShader(fragmentShader);//删除片段着色器

    //定义顶点
    GLfloat vertices[] = {
    -0.5f,  -0.5f, 0.0f, //顶点1
    0.5f, -0.5f, 0.0f, //顶点2
    0.0f, 0.5f, 0.0f  //顶点3
    };

    //VBO
    unsigned int VBO;
    glGenBuffers(1,&VBO);//生成VBO对象，ID是1
    glBindBuffer(GL_ARRAY_BUFFER,VBO);//把缓冲绑定到GL_ARRAY_BUFFER（缓冲类型）上
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);//把顶点绑定到缓冲中

    //VAO
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//配置顶点属性(位置0)
    glEnableVertexAttribArray(0);//启动位置0的顶点属性
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); //解绑，还原状态


    //激活程序对象
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        //背景颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //画三角形
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);//绑定VAO，使用其配置
        glDrawArrays(GL_TRIANGLES,0,3);//使用当前着色器程序和VAO绘制一个三角形

        glfwSwapBuffers(window);//交换前后缓冲区，绘制内容
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
        
    return 0;

}
void processInput(GLFWwindow *window)
{
    //检测是否按下了“ESC”键，如果按下了，就将窗口的关闭标志设置为true
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw回调
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}