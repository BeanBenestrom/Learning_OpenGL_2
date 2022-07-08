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


// float mixValue = 0;

// void processInput(GLFWwindow *window)
// {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);

//     if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
//     {
//         mixValue += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
//         if(mixValue >= 1.0f)
//             mixValue = 1.0f;
//     }
//     if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
//     {
//         mixValue -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
//         if (mixValue <= 0.0f)
//             mixValue = 0.0f;
//     }
// }


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

    // Triangle verticies and indices
    // GLfloat vertices[] = { 
    // //          POSITION         COLOR     TEXTURE                                   
    //     -0.5f,  -0.5f,  0.0f,   1, 0, 0,    0, 0,       // Bottom Left
    //      0.5f,  -0.5f,  0.0f,   0, 1, 0,    1, 0,       // Bottom right
    //      0.5f,   0.5f,  0.0f,   0, 0, 1,    1, 1,       // Upper right
    //     -0.5f,   0.5f,  0.0f,   1, 1, 1,    0, 1        // Upper left
    // };

    GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

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
        // Objects
        VAO vertexArray;
        VBO vertexBuffer(vertices, sizeof(vertices));
        EBO elementBuffer(indices, sizeof(indices));

        vertexArray.link_atribute(vertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), 0);
        vertexArray.link_atribute(vertexBuffer, 2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
        vertexArray.link_EBO(elementBuffer);

        //Activate¨
        shaderProgram.activate();
        vertexArray.bind();

        // Texture
        Texture texture("textures/Mr Bean God form 2.png", 0, GL_LINEAR, GL_REPEAT, GL_RGB);
        texture.bind();
        shaderProgram.set_uniform("tex0", 0);

        // 3D
        std::cout << "Aspect ratio: " << screenSettings::width/screenSettings::height << "\n";

        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f), 
            glm::vec3( 2.0f,  5.0f, -15.0f), 
            glm::vec3(-1.5f, -2.2f, -2.5f),  
            glm::vec3(-3.8f, -2.0f, -12.3f),  
            glm::vec3( 2.4f, -0.4f, -3.5f),  
            glm::vec3(-1.7f,  3.0f, -7.5f),  
            glm::vec3( 1.3f, -2.0f, -2.5f),  
            glm::vec3( 1.5f,  2.0f, -2.5f), 
            glm::vec3( 1.5f,  0.2f, -1.5f), 
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        // Camera space --> Screen space
        glm::mat4 projection; 
        projection = glm::perspective(cameraSettings::fov, (float)screenSettings::width/(float)screenSettings::height, 0.1f, 100.0f);
        shaderProgram.set_uniform("projection", projection);  

        while (!glfwWindowShouldClose(window))
        {
            // Delta time
            delta_time = (float)(glfwGetTime() - previous_time);
            previous_time = glfwGetTime();
            // std::cout << delta_time << " : " << 1/delta_time << " fps\n";

            // Draw objects
            for (int i = 0; i < 10; i++)
            {
                // Local space --> Global space
                glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
                model = glm::rotate(model, i * (float)(glfwGetTime()) * glm::radians(50.0f), cubePositions[i]);
                shaderProgram.set_uniform("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

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