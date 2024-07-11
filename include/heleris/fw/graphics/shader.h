#ifndef HRS_GRAPHICS_SHADER_H
#define HRS_GRAPHICS_SHADER_H

#include "../types.h"

enum EHRSShaderType {
    HRS_GL_SHADER_VERTEX,
    HRS_GL_SHADER_FRAGMENT,
};

typedef struct HRSShader {
    glObject_t glShader;
    enum EHRSShaderType type;
    char *source;
} HRSShader;

HRSShader* hrssh_create(enum EHRSShaderType type, char *source);

void hrssh_free(HRSShader *shader);

#endif