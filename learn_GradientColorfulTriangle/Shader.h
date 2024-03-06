#ifndef SHADER_H
#define SHADER_H

#include <string>
using namespace std;

class Shader
{

public:
    Shader(const char* vertexPath,const char* fragmentPath);
    string vertexString;
    string fragmentString;
    const char* vertexSource;
    const char* fragmentSource;
    unsigned int ID;
    void use();
};


#endif