#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shader.h"
#include "../VAO.h"
#include "../texture.h"


class Cube
{
private:
    glm::vec3 position;
    glm::vec4 color;
    VAO* object;
    Texture* texture;
    ShaderProgram* shader;

public:
    Cube(VAO* vao, ShaderProgram* shader, glm::vec3 position, glm::vec4 color);
    Cube(VAO* vao, ShaderProgram* shader, glm::vec3 position, float r, float g, float b, float a);
    Cube(VAO* vao, ShaderProgram* shader, float x, float y, float z, glm::vec4 color);
    Cube(VAO* vao, ShaderProgram* shader, float x, float y, float z, float r, float g, float b, float a);
    Cube(VAO* vao, ShaderProgram* shader, glm::vec3 position, Texture* texture);
    Cube(VAO* vao, ShaderProgram* shader, float x, float y, float z, Texture* texture);
    ~Cube();

    void draw();
};