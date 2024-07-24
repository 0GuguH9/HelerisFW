#ifndef HELERIS_FW_GRAPHICS_VAO_H
#define HELERIS_FW_GRAPHICS_VAO_H

#include "heleris/fw/types.h"

// VAO (Vertex Array Object) is the main render of a scene, holding VBOs.
typedef struct HRSVAO {
    glObject_t glVAO;
} HRSVAO;

// Heap manipulation

/*
 * Create a VAO (Vertex Array Object) object (you NEED to create a VAO BEFORE VBO).
 */
HRSVAO* hrsvao_create();

/*
 * Assert that the HRSRender object is not a nullptr.
 */
void hrsvao_assert(HRSVAO *_vao);

/*
 * Free a VAO.
 */
void hrsvao_free(HRSVAO *_vao);

// VAO related functions

/*
 * Bind current VAO for use
 */
void hrsvao_bind(HRSVAO *_vao);

/*
 * Unbind the current VBO
 */
void hrsvao_unbind();

#endif