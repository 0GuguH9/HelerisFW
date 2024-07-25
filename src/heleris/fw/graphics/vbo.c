#include "heleris/fw/graphics/vbo.h"

#include "heleris/fw/errors/error_presets.h"

#include <stdlib.h>

// Heap manipulation

HRSVBO* hrsvbo_create() {

    HRSVBO *_vbo = malloc(sizeof(HRSVBO));

    glGenBuffers(1, &_vbo->glVBO);

    return _vbo;
}

void hrsvbo_assert(HRSVBO *_vbo) {

    if (_vbo->glVBO)
        errpre_nullptr("HRSVBO");
}

void hrsvbo_free(HRSVBO *_vbo) {

    hrsvbo_assert(_vbo);

    free(_vbo);
    _vbo = nullptr;
}

// VBO binding

void hrsvbo_bind(HRSVBO *_vbo) {

    hrsvbo_assert(_vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbo->glVBO);
}

void hrsvbo_unbind() {

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Values manipulations (these data apply to tour current binded VBO)

void hrsvbo_addFloat(void *values, size_t values_byteSize, enum EHRSDrawType mode) {

    glBufferData(GL_ARRAY_BUFFER, values_byteSize, values, mode);
}

