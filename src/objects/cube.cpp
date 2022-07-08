#include <iostream>

#include "cube.h"


void Cube::draw()
{
    shader->activate();
    object->bind();

    if (texture != nullptr) { 
        texture->bind();
        shader->set_uniform("mode", 1);
    } else {
        shader->set_uniform("mode", 0);
        shader->set_uniform("color", color);
    }

    shader->set_uniform("model", glm::translate(glm::mat4(1.0f), position));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Cube::Cube overloading ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Cube::Cube(VAO* vao, ShaderProgram* shader, glm::vec3 position, glm::vec4 color)
{
    this->object = vao;
    this->shader = shader;
    this->position = position;
    this->color = color;
    this->texture = nullptr;
}

Cube::Cube(VAO* vao, ShaderProgram* shader, glm::vec3 position, float r, float g, float b, float a )
{
    this->object = vao;
    this->shader = shader;
    this->position = position;
    this->color = glm::vec4(r, g, b, a);
    this->texture = nullptr;
}

Cube::Cube(VAO* vao, ShaderProgram* shader, float x , float y , float z , glm::vec4 color)
{
    this->object = vao;
    this->shader = shader;
    this->position = glm::vec3(x, y, z);
    this->color = color;
    this->texture = nullptr;
}

Cube::Cube(VAO* vao, ShaderProgram* shader, float x , float y , float z , float r , float g , float b , float a )
{
    this->object = vao;
    this->shader = shader;
    this->position = glm::vec3(x, y, z);
    this->color = glm::vec4(r, g, b, a);
    this->texture = nullptr;
}


Cube::Cube(VAO* vao, ShaderProgram* shader, glm::vec3 position, Texture* texture)
{
    this->object = vao;
    this->shader = shader;
    this->position = position;
    this->texture = texture;
}

Cube::Cube(VAO* vao, ShaderProgram* shader, float x , float y , float z , Texture* texture)
{
    this->object = vao;
    this->shader = shader;
    this->position = glm::vec3(x, y, z);
    this->texture = texture;
}

Cube::~Cube() { }
