#include "config.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"

// OpenGL 3.3+ GLFW 3.3+ GLSL 3.3+
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

static void errorCallback(int error, const char* description);
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

int main(void)
{
    glfwSetErrorCallback(errorCallback);

    // init glfw
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    // config window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // create window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // set context
    glfwMakeContextCurrent(window);
    // input
    glfwSetKeyCallback(window, keyCallback);
    // window re-sizing
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glfwSetWindowSizeLimits(window, width, height, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetWindowAspectRatio(window, width, height);
    // load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    // frames until swapping buffers
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);

    // Main camera original settings - points towards +x
    CameraOptions mainCameraOptions = {glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f}; // position, worldUp, yaw, pitch
    ProjectionOptions mainProjectionOptions = {45.0f, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 100.0f}; // fov, aspectRatio, nearPlane, farPlane
    SensitivityOptions mainSensitivityOptions = {2.5f, 0.1f, 45.0f}; // moveSpeed, mouseSensitivity, zoom

    Camera mainCamera("mainCamera", mainCameraOptions, mainProjectionOptions, mainSensitivityOptions);
    mainCameraOptions.position = glm::vec3(0.0f, 3.0f, -5.0f);
    mainCameraOptions.yaw = 90.0f;
    Camera secondCamera("secondCamera", mainCameraOptions, mainProjectionOptions, mainSensitivityOptions);
    Camera::initWireframes();

    Shader testShader("../src/shaders/vertex.txt", "../src/shaders/fragment.txt");
    Texture testTexture("../src/assets/img/wall.jpg");

    float cube[] = {
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // render loop
    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        testShader.bind();
        
        //glm::mat4 view = mainCamera.getViewMatrix();
        //glm::mat4 projection = mainCamera.getProjectionMatrix();
        glm::mat4 view = Camera::getActiveCamera()->getViewMatrix();
        glm::mat4 projection = Camera::getActiveCamera()->getProjectionMatrix();
        glUniformMatrix4fv(glGetUniformLocation(testShader.getId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));;
        glUniformMatrix4fv(glGetUniformLocation(testShader.getId(), "view"), 1, GL_FALSE, glm::value_ptr(view));

        //glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        Camera::drawWireframes(testShader);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    Camera::cleanUp();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // destroy window && terminate glfw
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

static void errorCallback(int error, const char* description)
{
    fprintf(stderr, "\nError: %s\n\n", description);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // ESC - Close window
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    // Hold Z - Wireframe mode
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (key == GLFW_KEY_Z && action == GLFW_RELEASE)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    // WASD movement
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        Camera::setActiveCamera(1);
    }
    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
    {
        Camera::setActiveCamera(0);
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {

    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {

    }

}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // matches OpenGl window to glfw window
    glViewport(0, 0, width, height);
}