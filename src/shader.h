#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


GLuint compile_shader(const GLchar* shaderSource, GLenum shaderType);


class ShaderProgram {
private:
    bool _status = false;   // Is program functional
    bool _bind_status = false;

    std::string _vertexShaderSource;
    std::string _fragmentShaderSource;

    GLuint _id = 0;
    
public:
    ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
    ~ShaderProgram();

    void activate();
    void un_activate();

    void set_uniform(const GLchar* name, GLint data);
    void set_uniform(const GLchar* name, GLfloat data);
    void set_uniform(const GLchar* name, const glm::mat4& data);

    bool inline get_bind_status() { return _bind_status; }
    bool inline get_status() { return _status; }
    GLuint inline get_id() { return _id; }
};