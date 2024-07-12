#ifndef HRS_GRAPHICS_SHADER_H
#define HRS_GRAPHICS_SHADER_H

#include "../types.h"

enum EHRSShaderType {
    HRS_GL_SHADER_VERTEX,
    HRS_GL_SHADER_FRAGMENT,
};

/*
 * Represents an OpenGL shader object.
 */
typedef struct HRSShader {
    glObject_t glShader;
    enum EHRSShaderType type;
    char *source;
} HRSShader;


/*
 * Create a shader with a source
 */
HRSShader hrssh_create(enum EHRSShaderType type, char *source);

/*
 * Compile a shader (in this moment you can free the shader source) and set the source to nullptr.
 */
void hrssh_compile(HRSShader shader);

/*
 * Assert the GL shader ins't null.
 */
void hrssh_assert(HRSShader shader);

/*
 * Free a shader
 */
void hrssh_free(HRSShader shader);

#endif