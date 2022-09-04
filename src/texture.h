#pragma once

#include <glad/glad.h>
#include <string>


class Texture
{
private:
    bool _status;
    int _width, _height, _channels;
    GLuint _id;

public:
    Texture(const std::string& texturePath);
    Texture(const Texture& texture) = delete;
    Texture(Texture&& texture) = delete;
    ~Texture();

    void bind(GLenum slot = GL_TEXTURE1) const;

    // Get requests
    GLuint  inline get_id()         const { return _id;       }
    bool    inline get_status()     const { return _status;   }
    
    int     inline get_width()      const { return _width;    }
    int     inline get_height()     const { return _height;   }
    int     inline get_channels()   const { return _channels; }
};


// class Image
// {
// private:
//     GLuint _id;
//     GLenum _textureUnit;

// public:
//     Image(int width, int height, GLenum textureUnit, GLenum TEXTURE_FILTER, GLenum TEXTURE_WRAP, GLenum format);
//     ~Image();

//     void bind();
//     void un_bind();

//     GLuint inline get_id() { return _id; }
// };