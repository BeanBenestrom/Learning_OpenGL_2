#include "VAO.h"


VAO::VAO()
{
    glGenVertexArrays(1, &_id);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &_id);
}

void VAO::link_atribute(
    VBO &VBO, 
    GLuint layout, 
    GLuint componentNumber, 
    GLenum type, 
    GLboolean normalized, 
    GLsizei stride, 
    const GLvoid* offset
)
{
    // Get previous bound vertex and buffer arrays
    GLint64 bound_buffer_id, bound_vertex_array_id;
    glGetInteger64v(GL_ARRAY_BUFFER_BINDING, &bound_buffer_id);
    glGetInteger64v(GL_VERTEX_ARRAY_BINDING, &bound_vertex_array_id);

    // Link attributes
    glBindVertexArray(_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO.get_id());
    glVertexAttribPointer(layout, componentNumber, type, normalized, stride, offset);
    glEnableVertexAttribArray(layout);

    // Bind previous vertex and buffer arrays
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, bound_buffer_id);
    glBindVertexArray(bound_vertex_array_id);
}

void VAO::link_EBO(EBO &EBO)
{
    // Get previous bound vertex and element arrays
    GLint64 bound_element_id, bound_vertex_array_id;
    glGetInteger64v(GL_ELEMENT_ARRAY_BUFFER_BINDING, &bound_element_id);
    glGetInteger64v(GL_VERTEX_ARRAY_BINDING, &bound_vertex_array_id);

    // Link element array
    glBindVertexArray(_id);
    EBO.bind();

    // Bind previous vertex and element arrays
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bound_element_id);
    glBindVertexArray(bound_vertex_array_id);
}

void VAO::bind() 
{ 
    glBindVertexArray(_id); 
}

void VAO::un_bind() 
{
    glBindVertexArray(0); 
}