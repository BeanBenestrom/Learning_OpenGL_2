#include "VBO.h"


VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
    GLint64 bound_buffer_id;
    glGetInteger64v(GL_ARRAY_BUFFER_BINDING, &bound_buffer_id);

    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, bound_buffer_id);

    this->_size = size;
}

VBO::~VBO()
{
    glDeleteBuffers(1, &_id);
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VBO::un_bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}