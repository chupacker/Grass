#pragma once

#include <glad/gl.h>

class Vao {
public:
    Vao();

    void LinkAttrib(GLuint index, GLuint size, GLenum type, GLboolean normalized,
                    GLsizei stride, const GLvoid *pointer);

    void Bind();

private:
    GLuint ID;
};

class Vbo {
public:
    Vbo();

    void Bind();

    void Data(GLsizeiptr size, const GLvoid *data, GLenum usage);

private:
    GLuint ID;
};
