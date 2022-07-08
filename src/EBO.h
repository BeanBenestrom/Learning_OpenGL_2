#pragma once

#include <glad/glad.h>

class EBO
{
private:
    GLuint _id = 0;
    GLsizeiptr _size;

public:
    EBO(GLuint* indices, GLsizeiptr size);
    ~EBO();

    void bind();
    void un_bind();

    GLsizeiptr inline get_size() { return _size; }
    GLuint inline get_id() { return _id; }
};