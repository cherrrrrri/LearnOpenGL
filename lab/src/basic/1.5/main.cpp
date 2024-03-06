#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void bindTexture(GLuint& textureId, const char* path);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw初始化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw 配置
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
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

    // 开启深度测试
    glEnable(GL_DEPTH_TEST);

    // shader
    Shader ourShader("D:/openGLProject/lab/src/basic/1.5/shader.vs", "D:/openGLProject/lab/src/basic/1.5/shader.fs"); 

    #pragma region Model Data
    // 立方体
    float vertices[] = {
        // Rectangle 1
        -0.75f, -0.75f, 0.0f, 0.0f,
        -0.1f, -0.75f, 1.0f, 0.0f,
        -0.75f, -0.1f, 0.0f, 1.0f,
        -0.1f, -0.1f, 1.0f, 1.0f,
        
        // Rectangle 2
        0.1f, -0.75f, 0.0f, 0.0f,
        0.75f, -0.75f, 1.0f, 0.0f,
        0.1f, -0.1f, 0.0f, 1.0f,
        0.75f, -0.1f, 1.0f, 1.0f,
        
        // Rectangle 3
        -0.75f, 0.1f, 0.0f, 0.0f,
        -0.1f, 0.1f, 1.0f, 0.0f,
        -0.75f, 0.75f, 0.0f, 1.0f,
        -0.1f, 0.75f, 1.0f, 1.0f,
        
        // Rectangle 4
        0.1f, 0.1f, 0.0f, 0.0f,
        0.75f, 0.1f, 1.0f, 0.0f,
        0.1f, 0.75f, 0.0f, 1.0f,
        0.75f, 0.75f, 1.0f, 1.0f
    };

    int indices[] = {
        // Rectangle 1
        0, 1, 2,
        1, 2, 3,
        
        // Rectangle 2
        4, 5, 6,
        5, 6, 7,
        
        // Rectangle 3
        8, 9, 10,
        9, 10, 11,
        
        // Rectangle 4
        12, 13, 14,
        13, 14, 15
    };

    #pragma endregion
    
    // ----------纹理------------
    std::vector<unsigned int> texture;
    std::vector<std::string> path = {"D:/openGLProject/lab/src/basic/1.5/logo.png","D:/openGLProject/lab/src/basic/1.5/tex.png"};
    texture.resize(path.size());
    for(int i = 0; i < path.size(); i++){
        bindTexture(texture[i], path[i].c_str());
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    ourShader.use();
    ourShader.setInt("texture0", 0);  // Texture unit 0
    ourShader.setInt("texture1", 1);  // Texture unit 1


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // 渲染
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 因为开启了深度缓冲，所以每次在清空颜色缓冲的同时也要清空深度缓冲
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);
       
        ourShader.use();

        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        double milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

        // Compute blend ratio using sin function for oscillation effect and normalize to [0,1]
        // Adjust the frequency by dividing milliseconds by a value (e.g., 1000.0 for oscillation every second)
        float blendRatio = 0.5f * (std::sin(milliseconds / 1000.0) + 1.0f);

        ourShader.setFloat("blendRatio", blendRatio);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void bindTexture(GLuint& textureId, const char* path)
{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    stbi_set_flip_vertically_on_load(true);  
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 4)
            format = GL_RGBA;
        else if (nrChannels == 3)
            format = GL_RGB;
        else
            format = GL_RED;  // or handle other formats as needed
        
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}