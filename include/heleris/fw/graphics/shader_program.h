#ifndef HRS_GRAPHICS_SHADER_PROGRAM_H
#define HRS_GRAPHICS_SHADER_PROGRAM_H

#include "../types.h"
#include "shader.h"

/*
 * A Shader program is a way to agroup a vertex, a fragment and a opcional geometry shader
 */
typedef struct HRSShaderProgram {
    glObject_t glShaderProgram;
} HRSShaderProgram;

// Heap manipulation

/*
 * Create a shader program
 */
HRSShaderProgram* hrsshp_create();

/*
 * Assert that the HRSShaderProgram object is not a nullptr
 */
void hrsshp_assert(HRSShaderProgram *program);

/*
 * Free a HRSShaderProgram
 */
void hrsshp_free(HRSShaderProgram *program);

// GL functions

/*
 * Attach a shader to a shader program
 */
void hrsshp_attach(HRSShaderProgram *program, HRSShader *shader);

/*
 * Link the shader program
 */
void hrsshp_link(HRSShaderProgram *program);

/*
 * Active the current shader program for use
 */
void hrsshp_active(HRSShaderProgram *program);

#endif