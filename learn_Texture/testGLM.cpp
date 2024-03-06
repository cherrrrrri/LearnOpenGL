#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


using namespace std;
using namespace glm;

int main2(){
    // 一个四维向量
    vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);

    // 创建一个4*4单位矩阵
    mat4 trans = mat4(1.0f);

    // 生成变换矩阵
    // 对trans进行变换
    // translate用于平移变换,第二个参数是发生的变换
    trans = translate(trans, vec3(1.0f, 1.0f, 0.0f));

    // 四维向量进行变换
    vec = trans * vec;

    cout << vec.x << vec.y << vec.z << endl;

    return 0;

}