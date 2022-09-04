#pragma once

#include <glad/glad.h>

class EBO
{
private:
    GLuint _id;
    GLsizeiptr _size;

public:
    EBO(const GLuint* indices, GLsizeiptr size);
    EBO(const EBO& ebo) = delete;
    EBO(EBO&& ebo) = delete;
    ~EBO();

    void bind() const;
    void unbind() const;

    GLuint     inline get_id()      const { return _id;   }
    GLsizeiptr inline get_size()    const { return _size; }
};