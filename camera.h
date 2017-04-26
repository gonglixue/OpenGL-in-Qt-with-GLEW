#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
enum Camera_Movement{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front; // target - eye
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler angle
    GLfloat Yaw;
    GLfloat Pitch;
    GLfloat MovementSpeed;
    GLfloat MouseSensitivity;
    GLfloat Zoom;

    Camera(glm::vec3 position=glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           GLfloat yaw = YAW,
           GLfloat pitch = PITCH);

    // get the view matrix
    glm::mat4 GetViewMatrix(){
//        std::cout << "position: " << this->Position[0] << "," << this->Position[1] << "," << this->Position[2] << "\n";
//        std::cout << "front:" << this->Front[0] << "," << this->Front[1] << "," << this->Front[2] << "\n";
//        std::cout << "up:" << this->Up[0] << "," << this->Up[1] << "," << this->Up[2] << "\n";
//        std::cout << "yaw:" << this->Yaw << "\n";
//        std::cout << "zoom" << this->Zoom << "\n";
        return glm::lookAt(this->Position, this->Position+this->Front, this->Up);
    }

    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(GLfloat yoffset);

private:
    void updateCameraVectors();
};

#endif // CAMERA_H
