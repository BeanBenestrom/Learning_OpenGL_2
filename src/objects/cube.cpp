#include "cube.h"


Cube::Cube(const glm::vec3& position, Texture* texture, ShaderProgram* shader)
{
    this->position = position;
    this->texture = texture;
    this->shader = shader;
    this->color = glm::vec4(244, 14, 244, 1);

    // cubes.push_back(this*);
}


Cube::Cube(const glm::vec3& position, const glm::vec4& color, ShaderProgram* shader)
{
    this->position = position;
    this->color = color;
    this->shader = shader;

    this->texture = nullptr;
}


Cube::~Cube()
{

}