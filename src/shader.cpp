
#include <iostream>
#include <fstream>

#include "utility.h"

#include "shader.h"


GLuint compile_shader(const GLchar* shaderSource, GLenum shaderType)
{
    // Create shader
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    // Check compilation failure
    GLint compilation_success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compilation_success);
    if (compilation_success != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(shader, 1024, &log_length, message);
        
        std::cout << "[!] OPENGL - " << (shaderType == GL_VERTEX_SHADER ? "VERTEX SHADER" : "FRAGMENT SHADER") << " compilation error:\n" 
        << message << "\n";
        return GL_NONE;
    }

    return shader;
}


ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    // Load shader source -> src
    std::string vertexShaderSource, fragmentShaderSource;

    bool success1 = utility::load_text_from_file(vertexShaderSource, vertexShaderPath);
    bool success2 = utility::load_text_from_file(fragmentShaderSource, fragmentShaderPath);

    // Check for load failure
    if (!success1) { 
        std::cout << "[!] UTILITY - Could not load VERTEX SHADER from source file!\n    PATH: " << vertexShaderPath << "\n"; 
    }
    if (!success2) { 
        std::cout << "[!] UTILITY - Could not load FRAGMENT SHADER from source file!\n    PATH: " << fragmentShaderPath << "\n"; 
    }

    if (success1 && success2)
    {
        this->_vertexShaderSource = vertexShaderSource;
        this->_fragmentShaderSource = fragmentShaderSource;

        const GLchar* vsc = vertexShaderSource.c_str();
        const GLchar* fsc = fragmentShaderSource.c_str();

        // Compile shaders
        GLuint vertexShader = compile_shader(vsc, GL_VERTEX_SHADER);
        GLuint fragmentShader = compile_shader(fsc, GL_FRAGMENT_SHADER);

        if (vertexShader != GL_NONE and fragmentShader != GL_NONE)
        {
            // Create program
            GLuint shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);

            // Check for linking failure
            GLint link_success;
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &link_success);
            if (link_success != GL_TRUE)
            {
                GLsizei log_length = 0;
                GLchar message[1024];
                glGetProgramInfoLog(shaderProgram, 1024, &log_length, message);            
                std::cout << "[!] OPENGL - Program linking error:\n" << message << "\n";
            }

            // Delete shaders
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            this->_id = shaderProgram;
            this->_status = true;
        } 
    }
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(_id);
}

void ShaderProgram::activate() 
{ 
    glUseProgram(_id); 
}

void ShaderProgram::un_activate() 
{ 
    glUseProgram(0); 
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// set_uniform overloading //////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void ShaderProgram::set_uniform(const std::string& name, GLint data)
{
    glUseProgram(_id);
    if (uniform_map.find(name) == uniform_map.end()) { uniform_map[name] = glGetUniformLocation(_id, name.c_str()); }
    glUniform1i(uniform_map[name], data);
}

void ShaderProgram::set_uniform(const std::string& name, GLfloat data)
{
    glUseProgram(_id);
    if (uniform_map.find(name) == uniform_map.end()) { uniform_map[name] = glGetUniformLocation(_id, name.c_str()); }
    glUniform1f(uniform_map[name], data);
}

void ShaderProgram::set_uniform(const std::string& name, const glm::vec3& data)
{
    glUseProgram(_id);
    if (uniform_map.find(name) == uniform_map.end()) { uniform_map[name] = glGetUniformLocation(_id, name.c_str()); }
    glUniform3fv(uniform_map[name], 1, glm::value_ptr(data));
}

void ShaderProgram::set_uniform(const std::string& name, const glm::vec4& data)
{
    glUseProgram(_id);
    if (uniform_map.find(name) == uniform_map.end()) { uniform_map[name] = glGetUniformLocation(_id, name.c_str()); }
    glUniform4fv(uniform_map[name], 1, glm::value_ptr(data));
}

void ShaderProgram::set_uniform(const std::string& name, const glm::mat4& data)
{
    glUseProgram(_id);
    if (uniform_map.find(name) == uniform_map.end()) { uniform_map[name] = glGetUniformLocation(_id, name.c_str()); }
    glUniformMatrix4fv(uniform_map[name], 1, GL_FALSE, glm::value_ptr(data));
}