#include <iostream>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"
#include "camera.h"
#include "objects/cube.h"


namespace screenSettings
{
    const int width = 1000;
    const int height = 800;
}

namespace cameraSettings
{
    float fov = 45;
    float position[3] = {0, 0, 0};
    float rotation[2] = {0, 0};
    float speed = 10;
    float sensitivity = 0.1;
}

char error;

// Camera
Camera camera(
    glm::vec3(cameraSettings::position[0], cameraSettings::position[1], cameraSettings::position[2]), 
    glm::vec2(cameraSettings::rotation[0], cameraSettings::rotation[1]), 
    cameraSettings::speed,
    cameraSettings::sensitivity
);

//Mouse
float prev_mouse_x = screenSettings::width / 2;
float prev_mouse_y = screenSettings::height / 2;

// Delta time
float previous_time;
float delta_time;


void processInput(GLFWwindow *window, Camera &camera, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { camera.move(FORWARD, deltaTime); }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { camera.move(BACKWARD, deltaTime); }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { camera.move(LEFT, deltaTime); }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { camera.move(RIGHT, deltaTime); }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) { camera.move(UP, deltaTime); }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) { camera.move(DOWN, deltaTime); }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}


void mouse_movement(GLFWwindow* window, double xPos, double yPos)
{
    float x_pos = static_cast<float>(xPos);
    float y_pos = static_cast<float>(yPos);

    float xoffset = x_pos - prev_mouse_x;
    float yoffset = y_pos - prev_mouse_y;

    prev_mouse_x = x_pos;
    prev_mouse_y = y_pos;

    camera.rotate(xoffset, yoffset);
}


int main()
{
    std::cout << "Make cube\n";
    // Setup GLFW
    if (glfwInit() == GLFW_FALSE) { 
        std::cout << "[!] GLFW failed to intialize!\n";
        std::cin >> error;
        return 0; 
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Make window
    GLFWwindow *window = glfwCreateWindow(screenSettings::width, screenSettings::height, "Learning Open GL 2", NULL, NULL);
    if (!window) {  
        std::cout << "[!] GLFW window failed to be created!\n";
        glfwTerminate();
        std::cin >> error;
        return 0;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowPos(window, 800, 100);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_movement);

    // Setup Glad
    gladLoadGL();
    glViewport(0, 0, screenSettings::width, screenSettings::height);
    glEnable(GL_DEPTH_TEST);
    std::cout << glGetString(GL_VERSION) << "\n\n";

    // Make screen red
    glClearColor(1.0f, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    // Create shaderProgram
    ShaderProgram shaderProgram("shaders/vertexShader.vs", "shaders/fragmentShader.fs");
    if (!shaderProgram.get_status()) { 
        std::cerr << "[!] SHADER PROGRAM - Failed to create shader program!\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        std::cin >> error;
        return 0; 
    }

    {
        // Texture
        Texture texture("textures/Mr Bean God form 2.png", 0, GL_LINEAR, GL_REPEAT, GL_RGB);
        shaderProgram.set_uniform("tex0", 0);

        // Objects
        const GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f
        };

        const GLuint indices[] = {
            0, 1, 2,    2, 3, 0,
            4, 5, 6,    6, 7, 4,
            8, 9, 10,   10, 11, 8,
            12, 13, 14, 14, 15, 12,
            16, 17, 18, 18, 19, 16,
            20, 21, 22, 22, 23, 20,
        };

        VAO vertexArray;
        VBO vertexBuffer(vertices, sizeof(vertices));
        EBO elementBuffer(indices, sizeof(indices));
        vertexArray.link_atribute(vertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), 0);
        vertexArray.link_atribute(vertexBuffer, 2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
        vertexArray.link_EBO(elementBuffer);
        Cube cube1(&vertexArray, &shaderProgram, 3, 0, 0, 1, 0, 1, 1);
        Cube cube2(&vertexArray, &shaderProgram, 0, 0, 0, &texture);     

        // Camera space --> Screen space
        glm::mat4 projection; 
        projection = glm::perspective(cameraSettings::fov, (float)screenSettings::width/(float)screenSettings::height, 0.1f, 100.0f);
        shaderProgram.set_uniform("projection", projection);

        while (!glfwWindowShouldClose(window))
        {
            // Delta time
            delta_time = (float)(glfwGetTime() - previous_time);
            previous_time = glfwGetTime();

            // Draw objects
            cube1.draw(); cube2.draw();

            // Global space --> camera space
            glm::mat4 view = glm::rotate(glm::mat4(1.0f), -glm::radians(camera.get_rotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
            view = glm::rotate(view, -glm::radians(camera.get_rotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
            view = glm::translate(view, camera.get_position());
            shaderProgram.set_uniform("view", view);

            glfwSwapBuffers(window);
            
            // User input
            glfwPollEvents();
            processInput(window, camera, delta_time);

            // Clear
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_DEPTH_BUFFER_BIT);            
        }
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}