#include <iostream>

#include "settings.h"
#include "storage.h"



namespace storage
{
    namespace vertexArrays
    {
        // int add(VAO* vertexArray)
        // {
        //     vertexArray->link_atribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), 0);
        //     vertexArray->link_atribute(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
        //     _storage.push_back(vertexArray);

        //     return _storage.size() - 1;
        // }

        // void destroy()
        // {
        //     for (VAO* &vertexArray : _storage)
        //     {
        //         delete vertexArray;
        //     }
        // }


        // const VAO* get(int index)
        // {  
        //     if (index < 0 || index > _storage.size() - 1) return nullptr;
        //     else return _storage[index];
        // }
    } 

    namespace shaders
    {
        Shader* load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
        {
            if (_storage.find(vertexShaderPath + fragmentShaderPath) != _storage.end())
            {
                LOG("Load existing shader");
                return _storage[vertexShaderPath + fragmentShaderPath];
            }
            LOG("Create new shader");
            Shader* shaderProgram = new Shader(vertexShaderPath, fragmentShaderPath);

            if (!shaderProgram->get_program_status())
            {
                delete shaderProgram;
                return nullptr;
            }
            _storage[vertexShaderPath + fragmentShaderPath] = shaderProgram;
            return shaderProgram;
        }

        void destroy()
        {
            for (auto &pair : _storage)
            {
                delete pair.second;
            }
            _storage.clear();
        }
    } 

    namespace textures
    {
        Texture* load(const std::string& texturePath)
        {
            if (_storage.find(texturePath) != _storage.end())
            {
                LOG("Load existing texture");
                return _storage[texturePath];
            }
            LOG("Create new texture");
            Texture* texture = new Texture(texturePath);

            if (!texture->get_status())
            {
                delete texture;
                return nullptr;
            }
            _storage[texturePath] = texture;
            return texture;
        }

        void destroy()
        {
            for (auto &pair : _storage)
            {
                delete pair.second;
            }
            _storage.clear();
        }
    } 
}