#pragma once

#include <glad/glad.h>

#include "shader.h"
#include "VAO.h"


namespace Renderer
{
    void draw(const Shader& shader, const VAO& vao);
}