
#include <iostream>
#include <tuple>

#include "utility.h"
#include "shader.h"


GLuint compile_shader(const std::string& shaderSource, GLenum shaderType)
{
    const GLchar* src = shaderSource.c_str();   // glShaderSource requires const GLchar* const*

    // Create shader
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    // Check compilation failure
    GLint compilation_success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compilation_success);
    if (compilation_success != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(shader, 1024, &log_length, message);

        std::cerr << "[!] OPENGL - ";
        if (shaderType == GL_VERTEX_SHADER) std::cerr << "VERTEX SHADER";
        else if (shaderType == GL_FRAGMENT_SHADER) std::cerr << "FRAGMENT SHADER";
        else if (shaderType == GL_COMPUTE_SHADER) std::cerr << "COMPUTE SHADER";
        std::cerr << " compilation error:\n" << message << std::endl;
        
        return GL_NONE;
    }

    return shader;
}


Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	_programStatus = false;
    _vertexShaderStatus = true;
    _fragmentShaderStatus = true;

	// Load Source file
    auto [vertexShaderSource, vertexShaderSourceStatus] = utility::load_text_from_file(vertexShaderPath);
    auto [fragmentShaderSource, fragmentShaderSourceStatus] = utility::load_text_from_file(fragmentShaderPath);
    _vertexShaderSource = vertexShaderSource; _vertexShaderSourceStatus = vertexShaderSourceStatus;
    _fragmentShaderSource = fragmentShaderSource; _fragmentShaderSourceStatus = fragmentShaderSourceStatus;

    if (!vertexShaderSourceStatus)    { return; }
    if (!fragmentShaderSourceStatus)  { return; }

    // COMPILE REGULAR SHADER
    GLuint vertexShader = compile_shader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = compile_shader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    if (vertexShader == GL_NONE)    { _vertexShaderStatus = false;   return; }
    if (fragmentShader == GL_NONE)  { _fragmentShaderStatus = false; return; }

	// Link shaders
    _id = glCreateProgram();
    glAttachShader(_id, vertexShader);
    glAttachShader(_id, fragmentShader);
    glLinkProgram(_id);
    
    glDetachShader(_id, vertexShader);
    glDetachShader(_id, fragmentShader);
	glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);	

    // Check for linking failure
    GLint link_success;
    glGetProgramiv(_id, GL_LINK_STATUS, &link_success);
    if (link_success != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(_id, 1024, &log_length, message);            
        std::cerr << "[!] OPENGL - Program linking error:\n" << message << std::endl;

		return;
    }

	_programStatus = true;
}


Shader::~Shader()
{
    if (_vertexShaderStatus && _fragmentShaderStatus) glDeleteProgram(_id);
}


void Shader::activate() const
{
    glUseProgram(_id);
}


void Shader::deactivate() const
{ 
    glUseProgram(0); 
}


GLint Shader::get_uniform_location(const std::string& name)
{
    if (uniform_map.find(name) != uniform_map.end())
    {
        return uniform_map[name];
    }

    GLint location = glGetUniformLocation(_id, name.c_str());
    if (location == -1)
    {
        std::cerr << "[*] SHADER - Uniform does not exist!\n"
                  << "    NAME: " << name << "\n";
    }
    uniform_map[name] = location;
    return location;
}


void Shader::set_uniform(const std::string& name, GLint value)
{
    glUniform1i(get_uniform_location(name), value);
}


void Shader::set_uniform(const std::string& name, GLfloat data)
{
    glUniform1f(get_uniform_location(name), data);
}


void Shader::set_uniform(const std::string& name, const glm::vec3& vector)
{
    glUniform3fv(get_uniform_location(name), 1, glm::value_ptr(vector));
}


void Shader::set_uniform(const std::string& name, const glm::vec4& vector)
{
    glUniform4fv(get_uniform_location(name), 1, glm::value_ptr(vector));
}


void Shader::set_uniform(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(matrix));
}





ComputeShader::ComputeShader(const std::string& computeShaderPath)
{
	_programStatus = false;
    _computeShaderStatus = true;

	// Load Source file
    auto [_computeShaderSource, _computeShaderSourceStatus] = utility::load_text_from_file(computeShaderPath);
   
    // COMPILE REGULAR SHADER
    GLuint computeShader = compile_shader(_computeShaderSource, GL_COMPUTE_SHADER);

    if (computeShader == GL_NONE) { _computeShaderStatus = false; return; }

	// Link shaders
    _id = glCreateProgram();
    glAttachShader(_id, computeShader);
    glLinkProgram(_id);
    
    glDetachShader(_id, computeShader);
	glDeleteShader(computeShader);

    // Check for linking failure
    GLint link_success;
    glGetProgramiv(_id, GL_LINK_STATUS, &link_success);
    if (link_success != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(_id, 1024, &log_length, message);            
        std::cerr << "[!] OPENGL - Program linking error:\n" << message << "\n";

		return;
    }

	_programStatus = true;
}


ComputeShader::~ComputeShader()
{
	if (_computeShaderStatus) glDeleteProgram(_id);
}


void ComputeShader::activate() const
{
    glUseProgram(_id);
}

void ComputeShader::deactivate() const
{
    glUseProgram(0); 
}


GLint ComputeShader::get_uniform_location(const std::string& name)
{
    if (uniform_map.find(name) != uniform_map.end())
    {
        return uniform_map[name];
    }

    GLint location = glGetUniformLocation(_id, name.c_str());
    if (location == -1)
    {
        std::cerr << "[*] COMPUTE SHADER - Uniform does not exist!\n"
                  << "    NAME: " << name << "\n";
    }
    uniform_map[name] = location;
    return location;
}


void ComputeShader::set_uniform(const std::string& name, GLint value)
{
    glUniform1i(get_uniform_location(name), value);
}


void ComputeShader::set_uniform(const std::string& name, GLfloat data)
{
    glUniform1f(get_uniform_location(name), data);
}


void ComputeShader::set_uniform(const std::string& name, const glm::vec3& vector)
{
    glUniform3fv(get_uniform_location(name), 1, glm::value_ptr(vector));
}


void ComputeShader::set_uniform(const std::string& name, const glm::vec4& vector)
{
    glUniform4fv(get_uniform_location(name), 1, glm::value_ptr(vector));
}


void ComputeShader::set_uniform(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(matrix));
}