#ifndef HRS_GRAPHICS_RENDER_OPTIONS_H
#define HRS_GRAPHICS_RENDER_OPTIONS_H

#ifndef HELERIS_OPEN_GL_INCLUDE_ALREADY
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define HELERIS_OPEN_GL_INCLUDE_ALREADY
#endif

enum EHRSFilter {
    HRS_FILTER_NEAREST = GL_NEAREST,
    HRS_FILTER_LINEAR = GL_LINEAR,
};

enum EHRSTextureRenderOptions {
    HRS_TXT_R_OP_REPEAT = GL_REPEAT,
    HRS_TXT_R_OP_MIRROR_REPEAT = GL_MIRRORED_REPEAT,
    HRS_TXT_R_OP_CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
    HRS_TXT_R_OP_CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
};

enum EHRSPolygonMode {
    HRS_POLYGON_FILL = GL_FILL,
    HRS_POLYGON_LINE = GL_LINE,
};

typedef struct HRSRenderOptions {
    enum EHRSFilter _filter;
    enum EHRSTextureRenderOptions _textureRenderOptions;
    enum EHRSPolygonMode _polygonMode;
} HRSRenderOptions;

HRSRenderOptions hrsrop_create(enum EHRSFilter _filter, enum EHRSTextureRenderOptions _textureRenderOptions, enum EHRSPolygonMode _polygonMode);

void hrsrop_apply(HRSRenderOptions _renderOptions);

#endif