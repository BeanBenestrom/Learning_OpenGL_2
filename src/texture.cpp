#include <iostream>
#include <stb_image.h>

#include "texture.h"


Texture::Texture(const std::string& texturePath)
    : _status{false}, _width{0}, _height{0}, _channels{0}, _id{0}
{
    stbi_set_flip_vertically_on_load(1);
    unsigned char* bytes = stbi_load(texturePath.c_str(), &_width, &_height, &_channels, 4);

    if (!bytes)
    {
        std::cerr << "[*] TEXTURE - Could not load file data\n"
                  << "    PATH: " << texturePath << "\n";
        return;
    }

    glGenTextures(1, &_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes); 
}


Texture::~Texture()
{
    glDeleteTextures(1, &_id);
}


void Texture::bind(GLenum slot) const
{
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, _id);
}



// Image::Image(int width, int height, GLenum textureUnit, GLenum TEXTURE_FILTER, GLenum TEXTURE_WRAP, GLenum FORMAT)
// {
//     this->_textureUnit = textureUnit;

//     glGenTextures(1, &_id);
//     glActiveTexture(textureUnit);
//     glBindTexture(GL_TEXTURE_2D, _id);

//     if (TEXTURE_FILTER == GL_LINEAR) {
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     } else {
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//     }
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEXTURE_FILTER);

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TEXTURE_WRAP);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TEXTURE_WRAP);

//     glTexImage2D(GL_TEXTURE_2D, 0, FORMAT, width, height, 0, FORMAT, GL_UNSIGNED_BYTE, NULL);

//     glBindImageTexture(0, _id, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
// }

// Image::~Image()
// {
//     glDeleteTextures(1, &_id);
// }


// void Image::bind()
// {
//     glActiveTexture(_textureUnit);
//     glBindImageTexture(0, _id, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
// }

// void Image::un_bind()
// {
//     glActiveTexture(_textureUnit);
//     glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
// }