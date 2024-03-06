#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

using namespace std;
using namespace glm;


// 摄像机方向
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.5f;
const float ZOOM        =  60.0f;


class Camera
{
public:
    // 几个重要的参数
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // 欧拉角
    float Yaw;
    float Pitch;
    // 摄像机事件
    float MovementSpeed; // 摄像机的移动速度
    float MouseSensitivity; // 鼠标灵敏度
    float Zoom; // 缩放值

    // 包含向量的构造器
    Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position; // 摄像机位置
        WorldUp = up; // 上方向向量
        Yaw = yaw; // 沿y轴旋转角
        Pitch = pitch; // 沿x轴旋转角
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = vec3(posX, posY, posZ); // 摄像机位置
        WorldUp = vec3(upX, upY, upZ); // 上方向向量
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // 返回观察矩阵
    mat4 GetViewMatrix()
    {
        return lookAt(Position, Position + Front, Up); // 摄像机当前位置，想看的目标位置，指向上方的力量
    }

    // 对键盘事件的处理：摄像机位置的移动
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Up * velocity;
        if (direction == BACKWARD)
            Position -= Up * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    // 对鼠标移动事件的处理：摄像机方向的移动
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity; // 灵敏度越高，偏移数值越大
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // 对俯仰角的限制
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // 更新方向
        updateCameraVectors();
    }

    // 对鼠标滚动事件的处理：摄像机的缩放（远近）
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 60.0f)
            Zoom = 60.0f;
    }

private:
    // 更新向量
    void updateCameraVectors()
    {
        // 计算前向量
        vec3 front;
        front.x = cos(radians(Yaw)) * cos(radians(Pitch));
        front.y = sin(radians(Pitch));
        front.z = sin(radians(Yaw)) * cos(radians(Pitch));
        Front = normalize(front);
        // 重算右向量和上向量
        Right = normalize(cross(Front, WorldUp));  // 正交化
        Up    = normalize(cross(Right, Front));
    }
};




