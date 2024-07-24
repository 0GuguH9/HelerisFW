#ifndef HELERIS_FW_GRAPHICS_VBO_H
#define HELERIS_FW_GRAPHICS_VBO_H

#include "heleris/fw/types.h"

#ifndef HELERIS_OPEN_GL_INCLUDE_ALREADY
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define HELERIS_OPEN_GL_INCLUDE_ALREADY
#endif

/*
 * Just for avoiding invalid arguments
 */
enum HRSDrawType {
    HRS_GL_STREAM = GL_STREAM_DRAW,
    HRS_GL_STATIC = GL_STATIC_DRAW,
    HRS_GL_DYNAMIC = GL_DYNAMIC_DRAW,
};

/*
 * VBO (Vertex Buffer Object) is a GPU memory manipulator. 
 * We can define one VBO for every type of drawing, like:
 *  A VBO for tiles rendering
 *  A VBO for NPC rendering
 *  A VBO for liquids rendering
 *  A VBO for UI
 */
typedef struct HRSVBO {
    glObject_t glVBO;
} HRSVBO;

// Heap manipulation

/*
 * Create a VBO (Vertex Buffer Object)
 */
HRSVBO* hrsvbo_create();

/*
 * Assert that the HRSRender object is not a nullptr.
 */
void hrsvbo_assert(HRSVBO *_vbo);

/*
 * Free a VBO
 */
void hrsvbo_free(HRSVBO *_vbo);

// VBO related functions

/*
 * Bind a VBO
 */
void hrsvbo_bind(HRSVBO *_vbo);

/*
 * Unbind a VBO
 */
void hrsvbo_unbind();

void hrsvbo_addFloat();
void hrsvbo_addInt();
void hrsvbo_addUint();

#endif