#include <iostream>
#include <stb_image.h>

#include "texture.h"

Texture::Texture(const char* path, GLenum textureUnit, GLenum TEXTURE_FILTER, GLenum TEXTURE_WRAP, GLenum FORMAT)
{
    stbi_set_flip_vertically_on_load(true);
    this->_textureUnit = textureUnit;

    int width, height, numberOfColorChannels;
    unsigned char* bytes = stbi_load(path, &width, &height, &numberOfColorChannels, 0);

    if (!bytes) { std::cout << "[*] Texture - Could not load image\n    PATH: " << path << "\n"; }

    glGenTextures(1, &_id);
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, _id);

    if (TEXTURE_FILTER == GL_LINEAR) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEXTURE_FILTER);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TEXTURE_WRAP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TEXTURE_WRAP);

    glTexImage2D(GL_TEXTURE_2D, 0, FORMAT, width, height, 0, FORMAT, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_id);
}


void Texture::bind()
{
    glActiveTexture(_textureUnit);
    glBindTexture(GL_TEXTURE_2D, _id);

    _bind_state = true;
}

void Texture::un_bind()
{
    glActiveTexture(_textureUnit);
    glBindTexture(GL_TEXTURE_2D, 0);

    _bind_state = false;
}