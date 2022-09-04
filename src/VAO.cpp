#include "VAO.h"


VAO::VAO(const GLfloat* vertices, const GLuint* indices)
    : 
    _id{0}, 
    _vertice_count{sizeof(vertices) / sizeof(GLfloat)}, 
    _vbo{std::make_unique<VBO>(vertices, sizeof(vertices))}, 
    _ebo{std::make_unique<EBO>(indices, sizeof(indices))}
{
    glGenVertexArrays(1, &_id);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &_id);
}

void VAO::link_atribute(
    GLuint layout, 
    GLuint componentNumber, 
    GLenum type, 
    GLboolean normalized, 
    GLsizei stride, 
    const GLvoid* offset
)
{
    glBindVertexArray(_id);
    _vbo->bind();
    glVertexAttribPointer(layout, componentNumber, type, normalized, stride, offset);
    glEnableVertexAttribArray(layout);
}

void VAO::bind() const
{ 
    glBindVertexArray(_id); 
}

void VAO::unbind() const
{
    glBindVertexArray(0); 
}