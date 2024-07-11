#ifndef HRS_GRAPHICS_SHADER_PROGRAM_H
#define HRS_GRAPHICS_SHADER_PROGRAM_H

#include "shader.h"
#include "../types.h"

typedef struct HRSShaderProgram {
    glObject_t glShaderProgram;
    HRSShader *shaders_v;
    size_t shaders_c;
} HRSShaderProgram;

HRSShaderProgram* hrsshp_create();

void hrsshp_free(HRSShaderProgram *shaderProgram);

#endif