#pragma once

#include <glad/glad.h>


class Texture
{
private:
    GLuint _id;
    GLenum _textureUnit;

public:
    Texture(const char* path, GLenum textureUnit, GLenum TEXTURE_FILTER, GLenum TEXTURE_WRAP, GLenum format);
    ~Texture();

    void bind();
    void un_bind();

    GLuint inline get_id() { return _id; }
};


class Image
{
private:
    GLuint _id;
    GLenum _textureUnit;

public:
    Image(int width, int height, GLenum textureUnit, GLenum TEXTURE_FILTER, GLenum TEXTURE_WRAP, GLenum format);
    ~Image();

    void bind();
    void un_bind();

    GLuint inline get_id() { return _id; }
};