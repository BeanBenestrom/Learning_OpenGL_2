#include "VBO.h"
#include "settings.h"


VBO::VBO(const GLfloat* vertices, GLsizeiptr size)
    : _id{0}, _size{size}
{
    LOG("VBO Initialized");
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &_id);
}

void VBO::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VBO::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}