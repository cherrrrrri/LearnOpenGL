#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;


Shader::Shader(const char* vertexPath, const char* fragmentPath){
    // 1. 读取文件
    // file buffer
    ifstream vertexFile;
    ifstream fragmentFile;

    vertexFile.open(vertexPath);
    fragmentFile.open(fragmentPath);

    // fileString 转换成string buffer
    stringstream vertexSStream;
    stringstream fragmentSStream;

    // 是否读取成功
    try
    {
        if(!vertexFile.is_open()|| !fragmentFile.is_open()){
            throw exception("open file error");
        }

        // 把数据从硬盘中读到file string再导入到string buffer
        vertexSStream << vertexFile.rdbuf();
        fragmentSStream << fragmentFile.rdbuf();

        // 从string buffer到string
        vertexString = vertexSStream.str();
        fragmentString = fragmentSStream.str();

        // 从string到char*
        vertexSource = vertexString.c_str();
        fragmentSource = fragmentString.c_str();

        printf(vertexSource);
        printf(fragmentSource);


        // 2.编译着色器
        unsigned int vertex,fragment;
        int success;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexSource, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);//检查是否编译成功
        if(!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
        }


        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentSource, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        //检验链接着色器是否失败
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            cout << "ERROR::LINK_FAILED\n" << infoLog << endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    catch(const std::exception& e)
    {
        printf(e.what());
    }
    

    
}

void Shader::use(){
    glUseProgram(ID);
}
