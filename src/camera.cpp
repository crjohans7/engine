#include "camera.h"

// 16:9 & orange
const float Camera::wireframes[] = {0.0f, 0.0f, 0.0f, 1.0f, 0.6f, 0.2f,
                                    1.0f, -0.45f, -0.8f, 1.0f, 0.6f, 0.2f,
                                    1.0f, 0.45f, -0.8f, 1.0f, 0.6f, 0.2f,
                                    1.0f, 0.45f, 0.8f, 1.0f, 0.6f, 0.2f,
                                    1.0f, -0.45f, 0.8f, 1.0f, 0.6f, 0.2f};

const unsigned int Camera::indices[] = {0, 2, 1, 0, 3, 2, 0, 4, 3, 0, 1, 4};

std::vector<Camera*> Camera::cameraList = {};
unsigned int Camera::activeCamera = 0;
unsigned int Camera::wireframesVAO = 0;
unsigned int Camera::wireframesVBO = 0;
unsigned int Camera::wireframesEBO = 0;

Camera::Camera(const char* name, const CameraOptions c, const ProjectionOptions p, const SensitivityOptions s)
: position(c.position), worldUp(c.worldUp), yaw(c.yaw), pitch(c.pitch),
fov(p.fov), aspectRatio(p.aspectRatio), nearPlane(p.nearPlane), farPlane(p.farPlane),
moveSpeed(s.moveSpeed), mouseSensitivity(s.mouseSensitivity), scrollSensitivity(s.zoom)
{
    updateCameraVectors();

    // Limit number of cameras to 8
    if (Camera::cameraList.size() < 8)
    {
        Camera::cameraList.push_back(this);
    }
    else
    {
        fprintf(stderr, "\nError: Cannot make another camera\n\n");
    }
}

Camera* Camera::getActiveCamera() { return Camera::cameraList.empty() ? nullptr : Camera::cameraList[activeCamera]; }

std::vector<Camera*> Camera::getCameras() { return Camera::cameraList; }

void Camera::setActiveCamera(unsigned int idx) { Camera::activeCamera = idx; }

void Camera::setAspectRatio(float ratio) { aspectRatio = ratio; }

glm::mat4 Camera::getViewMatrix() { return glm::lookAt(position, position + front, up); }

glm::mat4 Camera::getProjectionMatrix() { return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane); }

void Camera::updateCameraVectors()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::initWireframes()
{
    glGenVertexArrays(1, &Camera::wireframesVAO);
    glGenBuffers(1, &Camera::wireframesVBO);
    glGenBuffers(1, &Camera::wireframesEBO);
    glBindVertexArray(Camera::wireframesVAO);
    glBindBuffer(GL_ARRAY_BUFFER, Camera::wireframesVBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(Camera::wireframes), Camera::wireframes, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Camera::wireframesEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Camera::indices), Camera::indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void Camera::drawWireframes(Shader& shader)
{
    shader.bind();
    glBindVertexArray(Camera::wireframesVAO);
    for (size_t i = 0; i < cameraList.size(); i++)
    {
        if (i == activeCamera) { continue; }

        Camera* camera = cameraList[i];
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, camera->position);
        model = glm::rotate(model, glm::radians(camera->yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(camera->pitch), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_LINE_LOOP, 12, GL_UNSIGNED_INT, 0);
    }
}

void Camera::cleanWireframes()
{
    glDeleteVertexArrays(1, &Camera::wireframesVAO);
    glDeleteBuffers(1, &Camera::wireframesVBO);
    glDeleteBuffers(1, &Camera::wireframesEBO);
}