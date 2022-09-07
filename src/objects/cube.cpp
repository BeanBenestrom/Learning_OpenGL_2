#include "../settings.h"
#include "../renderer.h"
#include "../storage.h"

#include "cube.h"


// Objects
static const GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
// static const GLuint indices[] = {
//     0, 1, 2,    2, 3, 0,
//     4, 5, 6,    6, 7, 4,
//     8, 9, 10,   10, 11, 8,
//     12, 13, 14, 14, 15, 12,
//     16, 17, 18, 18, 19, 16,
//     20, 21, 22, 22, 23, 20,
// };


Cube::Cube(float size, const glm::vec3& position, const std::string& texturePath, const std::string& fragmentShaderPath)
    : _size{size}, _position{position}, _color{glm::vec3(244, 14, 244)},
      _vertexArray{nullptr}, _shader{nullptr}, _texture{nullptr}
{
    // _vertexArray = storage::vertexArrays::load(something...);

    _vertexArray = std::make_unique<VAO>(vertices, sizeof(vertices));
    _vertexArray->link_atribute(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), 0);
    _vertexArray->link_atribute(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));

    _shader = storage::shaders::load(DEFAULT_VERTEX_SHADER, fragmentShaderPath);
    _texture = storage::textures::load(texturePath);

    if (_shader == nullptr) 
    {  
        std::cerr << "[*] CUBE - SHADER - Faled to load shader\n"
                  << "    VERTEX SHADER PATH: " << DEFAULT_VERTEX_SHADER << "\n"
                  << "    FRAGMENT SHADER PATH: " << fragmentShaderPath << "\n\n";
    }

    if (_texture == nullptr) 
    {  
        std::cerr << "[*] CUBE - TEXTURE - Faled to load texture\n"
                  << "    TEXTURE PATH: " << texturePath << "\n\n";
    }

    model = glm::translate(glm::mat4(1.0f), position);
    model = glm::scale(model, glm::vec3(size));
}


Cube::Cube(float size, const glm::vec3& position, const glm::vec3& color, const std::string& fragmentShaderPath)
    : _size{size}, _position{position}, _color{color},
      _vertexArray{nullptr}, _shader{nullptr}, _texture{nullptr}
{
    // _vertexArray = storage::vertexArrays::load(something...);

    _vertexArray = std::make_unique<VAO>(vertices, sizeof(vertices));
    _vertexArray->link_atribute(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), 0);
    _vertexArray->link_atribute(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));

    _shader = storage::shaders::load(DEFAULT_VERTEX_SHADER, fragmentShaderPath);

    if (_shader == nullptr) 
    {  
        std::cerr << "[*] CUBE - SHADER - Faled to load shader\n"
                  << "    VERTEX SHADER PATH: " << DEFAULT_VERTEX_SHADER << "\n"
                  << "    FRAGMENT SHADER PATH: " << fragmentShaderPath << "\n\n";
        return;
    }

    model = glm::translate(glm::mat4(1.0f), position);
    model = glm::scale(model, glm::vec3(size));
}


Cube::~Cube()
{

}


void Cube::draw()
{
    if (_shader != nullptr)
    {
        model = glm::translate(glm::mat4(1.0f), _position);
        model = glm::scale(model, glm::vec3(_size));
        _shader->set_uniform("model", model);
        
        if (_texture == nullptr)
        {
            _shader->set_uniform("color", _color);
            Renderer::draw(*_shader, *_vertexArray);
        }
        else
        {   
            _texture->bind();
            _shader->set_uniform("unit", 1);
            Renderer::draw(*_shader, *_vertexArray);
        }
    }
}