#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <glad/glad.h>

#include "shader.h"
#include "VAO.h"
#include "texture.h"


namespace storage
{
    // namespace vertexArrays
    // {
    //     static std::vector<VAO*> _storage;

    //     // Returns the index of the added vertex array
    //     int add(VAO* vertexArray);
    //     /* 
    //     index:
    //         1 - Cube
    //     */
    //     const VAO* get(int index);


    //     void destroy();
    // } 

    namespace shaders
    {
        static std::unordered_map<std::string, Shader*> _storage;

        // Returns a pointer to the shader
        // Returns nullptr if load failed
        Shader* load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

        void destroy();
    } 

    namespace textures
    {
        static std::unordered_map<std::string, Texture*> _storage;

        // Returns a pointer to the texture
        // Returns nullptr if load failed
        Texture* load(const std::string& texturePath);

        void destroy();
    } 
}
