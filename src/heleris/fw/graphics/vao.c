#include "heleris/fw/graphics/vao.h"

#include "heleris/fw/errors/error_presets.h"

#include <stdlib.h>

#ifndef HELERIS_OPEN_GL_INCLUDE_ALREADY
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define HELERIS_OPEN_GL_INCLUDE_ALREADY
#endif

// Heap manipulation

HRSVAO* hrsvao_create() {

    HRSVAO *_vao = malloc(sizeof(HRSVAO));

    glGenVertexArrays(1, &_vao->glVAO);

    return _vao;
}

void hrsvao_assert(HRSVAO *_vao) {

    if (_vao == nullptr)
        errpre_nullptr("HRSVAO");
}

void hrsvao_free(HRSVAO *_vao) {

    hrsvao_assert(_vao);

    free(_vao);
    _vao = nullptr;
}

// VAO related functions

void hrsvao_bind(HRSVAO *_vao) {

    hrsvao_assert(_vao);
    
    glBindVertexArray(_vao->glVAO);
}

void hrsvao_unbind() {

    glBindVertexArray(0);
}
