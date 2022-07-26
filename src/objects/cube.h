#pragma once


#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shader.h"
#include "../texture.h"


class Cube 
{
private:
    glm::vec3 position;
    glm::vec4 color;

    ShaderProgram* shader;
    Texture* texture;

public:
    static std::vector<Cube*> cubes;

    Cube(const glm::vec3& position, Texture* texture, ShaderProgram* shader);
    Cube(const glm::vec3& position, const glm::vec4& color, ShaderProgram* shader);
    ~Cube();

    void draw();

    glm::vec3 inline get_position() { return position; }
    glm::vec4 inline get_color() { return color; }
    ShaderProgram* get_shader() { return shader; }
};