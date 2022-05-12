#include "Shader.h"
#include "Camera.h"
#include "Shape.h"
#include "Mesh.h"

#define SDL_MAIN_HANDLED
#define STB_IMAGE_IMPLEMENTATION

#include <glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <iostream>

//http://casual-effects.com/data/index.html

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;	
float lastFrame = 0.0f;

// Player
GameObject player;

int main()
{
    // Initialize and configure glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Initialize Window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Scene", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Set callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    //std::cout << "OpenGL version supported by this platform: " << glGetString(GL_VERSION) << std::endl;

    // Disable the mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // Init shader
    Shader ourShader("assets/camera.vs", "assets/camera.fs");

    Texture texture1;
    texture1.LoadFromFile("assets/container.png");


    // Load Models
    Shape cube = Shape::LoadFromFile("assets/cube.txt");

    Mesh mesh = Mesh();
    mesh.SetShape(cube);
    mesh.textures.push_back(texture1);

    player = GameObject();

    // Tell OpenGL for each sampler to which texture unit it belongs to
    ourShader.Use();
    ourShader.SetUniform("texture1", 0);

    ourShader.SetUniform("lightColor", 1.0f, 1.0f, 1.0f);
    ourShader.SetUniform("lightPos", 2.4f, 2.0f, 4.0f);
    //lightPos *= 2;

    float rotation = 0;

    // Render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // Frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);

        // Render
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1.id);

        // Activate shader
        ourShader.Use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.SetUniform("projection", projection);

        // Camera view Transform
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.SetUniform("view", view);
        ourShader.SetUniform("viewPos", camera.GetPosition());

        player.Rotate({ 0.01f, 0, 0 });        
        mesh.Draw(ourShader, player.GetPosition(), player.GetEular());

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Unallocate resources
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);

    // Terminate
    glfwTerminate();
    return 0;
}

// Process all input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.OnKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.OnKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.OnKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.OnKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_UP   ) == GLFW_PRESS) player.Move(camera.GetFront() * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS) player.Move(-camera.GetFront() * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS) player.Move(-camera.GetRight() * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) player.Move(camera.GetRight() * deltaTime);
}

// Window resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


// Mouse move callback
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Y is reversed

    lastX = xpos;
    lastY = ypos;

    camera.OnMouseMovement(xoffset, yoffset);
}

// Mouse scroll wheel callback
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.OnMouseScroll(static_cast<float>(yoffset));
}