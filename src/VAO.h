#pragma once


#include <memory>
#include <glad/glad.h>

#include "VBO.h"
#include "EBO.h"

class VAO
{
private:
    GLuint _id;
    GLsizei _vertice_count;

    std::unique_ptr<VBO> _vbo;
    std::unique_ptr<EBO> _ebo;

public:
    VAO(
        const GLfloat* vertices, std::size_t vertice_sizeof, 
        const GLuint* indices,   std::size_t indices_sizeof
    );
    VAO(const VAO& vao) = delete;
    VAO(VAO&& vao) = delete;
    ~VAO();

    void link_atribute(
        GLuint layout, 
        GLuint componentNumber, 
        GLenum type, 
        GLboolean normalized, 
        GLsizei stride, 
        const GLvoid* offset
    );

    void bind() const;
    void unbind() const;

    GLuint  inline get_id()    const { return _id;            }
    int     inline get_count() const { return _vertice_count; }
};