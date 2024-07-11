#ifndef HRS_GRAPHICS_DRAW_BATCH_H
#define HRS_GRAPHICS_DRAW_BATCH_H

#include "render_options.h"
#include "shader_program.h"
#include "../types.h"

typedef struct HRSRender {
    HRSShaderProgram shaderProgram;
    enum HRSFilter filter;
} HRSRender;

#endif