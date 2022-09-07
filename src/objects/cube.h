#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../VAO.h"
#include "../shader.h"
#include "../texture.h"


class Cube 
{
private:
    bool _status;

    float _size;
    glm::vec3 _position;
    glm::vec3 _color;

    std::unique_ptr<VAO> _vertexArray;
    Shader* _shader;
    Texture* _texture; 

    glm::mat4 model;
    
public:
    Cube(float size, const glm::vec3& position, const std::string& texturePath, const std::string& shaderPath);
    Cube(float size, const glm::vec3& position, const glm::vec3& color, const std::string& shaderPath);
    ~Cube();

    void draw();

    Shader* get_shader() { return _shader; }
    Texture* get_texture() { return _texture; } 

    void set_size(float size)                    { _size = size;         }
    void set_position(const glm::vec3& position) { _position = position; }
    void set_color(const glm::vec3& color)       { _color = color;       }

    bool      inline get_status()   const { return _status;   }
    float     inline get_size()     const { return _size;     }
    glm::vec3 inline get_position() const { return _position; }
    glm::vec3 inline get_color()    const { return _color;    } 
};