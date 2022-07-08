#pragma once

#include <glad/glad.h>


class Texture
{
private:
    GLuint _id;
    GLenum _textureUnit;
    bool _bind_state = false;

public:
    Texture(const char* path, GLenum textureUnit, GLenum TEXTURE_FILTER, GLenum TEXTURE_WRAP, GLenum format);
    ~Texture();

    void bind();
    void un_bind();

    bool inline get_bind_state() { return _bind_state; }
    GLuint inline get_id() { return _id; }
};