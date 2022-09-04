#include "storage.h"



namespace storage
{
    namespace vertexArrays
    {
        void init()
        {
            // Cube
            const GLfloat vertices[] = {
                -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,

                0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f
            };


            const GLuint indices[] = {
                0, 1, 2,    2, 3, 0,
                4, 5, 6,    6, 7, 4,
                8, 9, 10,   10, 11, 8,
                12, 13, 14, 14, 15, 12,
                16, 17, 18, 18, 19, 16,
                20, 21, 22, 22, 23, 20,
            };

            VAO* vertexArray = new VAO(vertices, indices);
            
            vertexArray->link_atribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), 0);
            vertexArray->link_atribute(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
            _storage.push_back(vertexArray);
        }

        void destroy()
        {
            for (VAO* &vertexArray : _storage)
            {
                delete vertexArray;
            }
        }
    } 
}