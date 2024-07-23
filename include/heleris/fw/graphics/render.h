#ifndef HRS_GRAPHICS_DRAW_BATCH_H
#define HRS_GRAPHICS_DRAW_BATCH_H

#include "vbo.h"
#include "vao.h"
#include "render_options.h"
#include "shader_program.h"

/*
 * Represent a render struct.
 * This struct is used only on drawing GUI and your context, so if you don't want to use, its fine!
 * You can make your own drawing GUI and object system.
 * You can use only the struct.
 */
typedef struct HRSRender {
    HRSShaderProgram *_shaderProgram;
    HRSRenderOptions _renderOptions;
    HRSVAO *_vao;
    HRSVBO *_vbo;
} HRSRender;

// Heap manipulation

/*
 * Create a render object.
 */
HRSRender* hrsr_create(HRSShaderProgram *_shaderProgram, HRSRenderOptions _renderOptions, HRSVAO *_vao, HRSVBO *_vbo);

/*
 * Assert that the HRSRender object is not a nullptr
 */
void hrsr_assert(HRSRender *_render);

/*
 * Start rendering.
 * Apply these settings:
 *  - Use shaders.
 *  - Apply render options.
 * Only use if you want to use this style (i.e. making your only presets) and not the drawbatch style
 */
void hrsr_startRender(HRSRender *_render);

/*
 * Free a render.
 */
void hrsr_free(HRSRender *_render);

#endif