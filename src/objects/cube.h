#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shader.h"
#include "../texture.h"


class Cube 
{
private:
    glm::vec3 _position;
    glm::vec4 _color;

    std::unique_ptr<Shader> _shader;
    std::unique_ptr<Texture> _texture;

public:
    Cube(const glm::vec3& position, const std::string& texturePath, const std::string& shaderPath);
    Cube(const glm::vec3& position, const glm::vec4& color, const std::string& shaderPath);
    ~Cube();

    void draw();

    glm::vec3 inline get_position() { return _position; }
    glm::vec4 inline get_color()    { return _color;    }
};