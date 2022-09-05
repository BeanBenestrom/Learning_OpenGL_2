#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "settings.h"
#include "shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"
#include "camera.h"
#include "renderer.h"
#include "storage.h"

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
float previous_time = 0.0f;
float delta_time = 0.0f;


#ifdef _DEBUG
void APIENTRY glDebugOutput(GLenum source, 
                            GLenum type, 
                            unsigned int id, 
                            GLenum severity, 
                            GLsizei length, 
                            const char *message, 
                            const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

    std::cerr << "---------------" << std::endl;
    std::cerr << "Debug message (" << id << "): " <<  message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cerr << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cerr << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cerr << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cerr << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cerr << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cerr << "Source: Other"; break;
    } std::cerr << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cerr << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cerr << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cerr << "Type: Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY:         std::cerr << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cerr << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cerr << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cerr << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cerr << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cerr << "Type: Other"; break;
    } std::cerr << std::endl;
    
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cerr << "Severity: !!"; break;    // High
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cerr << "Severity: !"; break;     // Medium
        case GL_DEBUG_SEVERITY_LOW:          std::cerr << "Severity: *"; break;     // Low
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cerr << "Severity: @"; break;     // Notification
    } std::cerr << std::endl;
    std::cerr << std::endl;
}
#endif


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
    char _end[100];
    std::cout << "\n" << MODE << " mode is enabled\n";

    // Setup GLFW
    if (glfwInit() == GLFW_FALSE) { 
        std::cerr << "[!] GLFW failed to intialize!\n";
        std::cin.get(_end, 100);
        return -1; 
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

    // Make window
    GLFWwindow *window = glfwCreateWindow(screenSettings::width, screenSettings::height, "Learning Open GL 2", NULL, NULL);
    if (!window) {  
        std::cerr << "[!] GLFW window failed to be created!\n";
        glfwTerminate();
        std::cin.get(_end, 100);
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowPos(window, 800, 100);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_movement);
    glfwSwapInterval(0);

    // Setup Glad
    gladLoadGL();
    glViewport(0, 0, screenSettings::width, screenSettings::height);
    glEnable(GL_DEPTH_TEST);
    std::cout << glGetString(GL_VERSION) << "\n\n";

#ifdef _DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
    glDebugMessageCallback(glDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif

    {
        Cube cube1(2.0f, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}, "shaders/fragmentShader.fs");
        Cube cube2(2.0f, glm::vec3{5.0f, 0.0f, 0.0f}, "textures/Mr Bean God form 2.png", "shaders/fragmentShaderTex.fs");

        // Camera space --> Screen space
        glm::mat4 projection; 
        glm::mat4 view;
        projection = glm::perspective(cameraSettings::fov, (float)screenSettings::width/(float)screenSettings::height, 0.1f, 100.0f);
        cube1.get_shader()->activate();
        cube1.get_shader()->set_uniform("projection", projection);
        cube2.get_shader()->activate();
        cube2.get_shader()->set_uniform("projection", projection);

        // ImGui
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 430");

        // Save lag
        float temp_deltaTime = 0.0f;

        while (!glfwWindowShouldClose(window))
        {
            // Delta time
            delta_time = (float)(glfwGetTime() - previous_time);
            previous_time = glfwGetTime();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Text("Application average %.3f ms (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            if (0.02f <= delta_time) {
                temp_deltaTime = delta_time;
                ImGui::Text("Delta time %.1f FPS   D:<", 1.0f / delta_time);
            }
            else {
                ImGui::Text("Delta time %.1f FPS", 1.0f / delta_time);
            }
            ImGui::Text("Last lag %.1f FPS", 1.0f / temp_deltaTime);

            // Draw objects

            cube1.draw();
            cube2.draw();

            // Global space --> camera space
            view = glm::rotate(glm::mat4(1.0f), -glm::radians(camera.get_rotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
            view = glm::rotate(view, -glm::radians(camera.get_rotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
            view = glm::translate(view, camera.get_position());
            cube1.get_shader()->activate();
            cube1.get_shader()->set_uniform("view", view);
            cube2.get_shader()->activate();
            cube2.get_shader()->set_uniform("view", view);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
    storage::shaders::destroy();
    storage::textures::destroy();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}