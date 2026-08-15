#include "Buffers.h"


Vao::Vao() {
    glGenVertexArrays(1, &ID);
}

void Vao::LinkAttrib(GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizei stride,
                     const GLvoid *pointer) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}

void Vao::Bind() {
    glBindVertexArray(ID);
}


Vbo::Vbo() {
    glGenBuffers(1, &ID);
}

void Vbo::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, Vbo::ID);
}

void Vbo::Data(GLsizeiptr size, const GLvoid *data, GLenum usage) {
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}
