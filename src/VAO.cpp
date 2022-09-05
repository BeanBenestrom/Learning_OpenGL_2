#include "VAO.h"


VAO::VAO(
    const GLfloat* vertices, std::size_t vertice_sizeof, 
    const GLuint* indices,   std::size_t indices_sizeof
)   : 
    _id{0}, 
    _vertice_count{static_cast<GLsizei>(vertice_sizeof / sizeof(GLfloat))}, 
    _vbo{std::make_unique<VBO>(vertices, vertice_sizeof)}, 
    _ebo{std::make_unique<EBO>(indices, indices_sizeof)}
{
    glGenVertexArrays(1, &_id);

    glBindVertexArray(_id);
    _ebo->bind();
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