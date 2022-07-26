#pragma once

#include <string>
#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


GLuint compile_shader(const GLchar* shaderSource, GLenum shaderType);


class ShaderProgram {
private:
    bool _status = false;   // Is program functional

    std::string _vertexShaderSource;
    std::string _fragmentShaderSource;

    GLuint _id = 0;
    std::unordered_map<std::string, GLuint> uniform_map;
    
public:
    ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
    ~ShaderProgram();

    void activate();
    void un_activate();

    void set_uniform(const std::string& name, GLint data);
    void set_uniform(const std::string& name, GLfloat data);
    void set_uniform(const std::string& name, const glm::vec3& data);
    void set_uniform(const std::string& name, const glm::vec4& data);
    void set_uniform(const std::string& name, const glm::mat4& data); 

    bool inline get_status() const { return _status; }
    GLuint inline get_id() const { return _id; }
};


class ComputeShader 
{
private:
    bool _status = false;   // Is program functional

    std::string _computeShaderSource;
    GLuint _id = 0;
    
public:
    ComputeShader(const char* computeShaderPath);
    ~ComputeShader();

    void activate();
    void un_activate();

    bool inline get_status() const { return _status; }
    GLuint inline get_id() const { return _id; }
};