#pragma once

#include <string>
#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


GLuint compile_shader(const GLchar* shaderSource, GLenum shaderType);


class Shader
{
private:  
    bool _vertexShaderSourceStatus;
    bool _fragmentShaderSourceStatus;

    bool _vertexShaderStatus;
    bool _fragmentShaderStatus;

    bool _programStatus;

    GLuint _id = 0;

    std::string _vertexShaderSource;
    std::string _fragmentShaderSource;

    std::unordered_map<std::string, GLint> uniform_map;

public:
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    Shader(const Shader& _shader) = delete;
    Shader(Shader&& _shader) = delete;
    ~Shader();

    void activate() const;
    void deactivate() const;

    GLint get_uniform_location  (const std::string& name);
    void  set_uniform           (const std::string& name, GLint value);
    void  set_uniform           (const std::string& name, GLfloat value);
    void  set_uniform           (const std::string& name, const glm::vec3& vector);
    void  set_uniform           (const std::string& name, const glm::vec4& vector);
    void  set_uniform           (const std::string& name, const glm::mat4& matrix);

    GLuint inline get_id()              const { return _id;            }
    bool   inline get_program_status()  const { return _programStatus; }
};


class ComputeShader
{
private:
    bool _computeShaderSourceStatus;
    bool _computeShaderStatus;
    bool _programStatus;

    GLuint _id = 0;

    std::string _computeShaderSource;

    std::unordered_map<std::string, GLint> uniform_map;

public:
    ComputeShader(const std::string& computeShaderPath);
    ComputeShader(const ComputeShader& _shader) = delete;
    ComputeShader(ComputeShader&& _shader) = delete;
    ~ComputeShader();

    void activate() const;
    void deactivate() const;

    GLint get_uniform_location  (const std::string& name);
    void  set_uniform           (const std::string& name, GLint value);
    void  set_uniform           (const std::string& name, GLfloat value);
    void  set_uniform           (const std::string& name, const glm::vec3& vector);
    void  set_uniform           (const std::string& name, const glm::vec4& vector);
    void  set_uniform           (const std::string& name, const glm::mat4& matrix);

    GLuint inline get_id()              const { return _id;            }
    bool   inline get_program_status()  const { return _programStatus; }
};
