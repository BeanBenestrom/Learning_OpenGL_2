#pragma once

#include <glad/glad.h>

class VBO
{
private:
    GLuint _id;
    GLsizeiptr _size;

public:
    VBO(const GLfloat* vertices, GLsizeiptr size);
    VBO(const VBO& vbo) = delete;
    VBO(VBO&& vbo) = delete;
    ~VBO();

    void bind() const;
    void unbind() const;

    GLsizeiptr inline get_size() const  { return _size; }
    GLuint     inline get_id()   const  { return _id;   }
};