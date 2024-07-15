#ifndef HRS_GRAPHICS_DRAW_BATCH_H
#define HRS_GRAPHICS_DRAW_BATCH_H

#include "render_options.h"
#include "shader_program.h"

/*
 * Represent a render struct.
 * This struct is used only on drawing GUI and your context, so if you don't want to use, its fine!
 * You can make your own drawing GUI and object system.
 * You can use only the struct.
 */
typedef struct HRSRender {
    HRSShaderProgram *shaderProgram;
    enum HRSFilter filter;
    enum HRSTextureRenderOptions textureRenderOptions;
} HRSRender;

/*
 * Create a render object.
 */
HRSRender* hrsr_create();

/*
 * Start rendering.
 * Only use if you want to use this style (i.e. making your only presets)
 */
void hrsr_startRender(HRSRender *render);

/*
 * Free a render.
 */
void hrsr_free(HRSRender *render);

#endif