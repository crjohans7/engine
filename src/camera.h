#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "shader.h"

// Could provide default values in these structs if necessary

struct CameraOptions {
    glm::vec3 position;
    glm::vec3 worldUp;
    float yaw;
    float pitch;
};

struct ProjectionOptions {
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
};

struct SensitivityOptions {
    float moveSpeed;
    float mouseSensitivity;
    float zoom;
};

class Camera
{
private:
    static const float wireframes[];
    static const unsigned int indices[];
    static std::vector<Camera*> cameraList;
    static unsigned int activeCamera, wireframesVAO, wireframesVBO, wireframesEBO;
    glm::vec3 position, front, up, right, worldUp;
    float yaw, pitch, fov, aspectRatio, nearPlane, farPlane, moveSpeed, mouseSensitivity, scrollSensitivity;
public:
    Camera(const char* name, const CameraOptions c, const ProjectionOptions p, const SensitivityOptions s);
    static Camera* getActiveCamera();
    static std::vector<Camera*> getCameras();
    static void setActiveCamera(unsigned int idx);
    void setAspectRatio(float ratio);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    void updateCameraVectors();
    static void initWireframes();
    static void drawWireframes(Shader& shader);
    static void cleanWireframes();
};

#endif