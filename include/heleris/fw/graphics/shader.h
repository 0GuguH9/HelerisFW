#ifndef HRS_GRAPHICS_SHADER_H
#define HRS_GRAPHICS_SHADER_H

#ifndef HELERIS_OPEN_GL_INCLUDE_ALREADY
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define HELERIS_OPEN_GL_INCLUDE_ALREADY
#endif

#include "../types.h"

enum EHRSShaderType {
    HRS_GL_SHADER_VERTEX = GL_VERTEX_SHADER,
    HRS_GL_SHADER_FRAGMENT = GL_FRAGMENT_SHADER,
    HRS_GL_SHADER_GEOMETRY = GL_GEOMETRY_SHADER,
};

enum EHRSGLSLType {
    HRS_GL_GLSL_UBYTE = GL_UNSIGNED_BYTE,
    HRS_GL_GLSL_SHORT = GL_SHORT,
    HRS_GL_GLSL_USHORT = GL_UNSIGNED_SHORT,
    HRS_GL_GLSL_INT = GL_INT,
    HRS_GL_GLSL_UINT = GL_UNSIGNED_INT,
    HRS_GL_GLSL_HALF = GL_HALF_FLOAT,
    HRS_GL_GLSL_FLOAT = GL_FLOAT,
    HRS_GL_GLSL_DOUBLE = GL_DOUBLE,
};

/*
 * Represents an OpenGL shader object.
 */
typedef struct HRSShader {
    glObject_t glShader;
    enum EHRSShaderType type;
    const char *source;
} HRSShader;


/*
 * Create a shader with a source.
 */
HRSShader* hrssh_create(const enum EHRSShaderType type, const char *source);

/*
 * Compile a shader and set the source to nullptr.
 * You can delete/free the source if is a heap object.
 */
void hrssh_compile(HRSShader *_shader);

/*
 * Assert the GL shader ins't null.
 */
void hrssh_assert(const HRSShader *_shader);

/*
 * Free a shader.
 */
void hrssh_free(HRSShader *_shader);

// Vertex Shader ONLY

void hrssh_vertex_add(int location, size_t value_s, enum EHRSGLSLType type, bool normalize, size_t stride, size_t offset);

#endif