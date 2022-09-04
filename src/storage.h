#pragma once

#include <vector>
#include <string>
#include <memory>
#include <glad/glad.h>

#include "shader.h"
#include "VAO.h"
#include "texture.h"


namespace storage
{
    namespace vertexArrays
    {
        static std::vector<VAO*> _storage;

        void init();
        void destroy();

        // template<class T>
        // void add_vertex_array()
        // {

        // }
    } 
}
