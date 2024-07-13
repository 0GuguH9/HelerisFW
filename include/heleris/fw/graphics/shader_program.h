#ifndef HRS_GRAPHICS_SHADER_PROGRAM_H
#define HRS_GRAPHICS_SHADER_PROGRAM_H

#include "../types.h"

typedef struct HRSShaderProgram {
    glObject_t glShaderProgram;
} HRSShaderProgram;

HRSShaderProgram* hrsshp_create();

void hrsshp_free(HRSShaderProgram *shaderProgram);

#endif