#include "renderer.h"


void Renderer::draw(const Shader& shader, const VAO& vao)
{
    shader.activate();
    vao.bind();
    glDrawElements(GL_TRIANGLES, vao.get_count(), GL_UNSIGNED_INT, (const void*)0);
}