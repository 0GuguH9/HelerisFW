#ifndef HRS_GRAPHICS_RENDER_OPTIONS_H
#define HRS_GRAPHICS_RENDER_OPTIONS_H

enum HRSFilter {
    HRS_FILTER_NEAREST,
    HRS_FILTER_LINER,
};

enum HRSTextureRenderOptions {
    HRS_TXT_R_OP_REPEAT,
    HRS_TXT_R_OP_MIRROR_REPEAT,
    HRS_TXT_R_OP_CLAMP_TO_EDGE,
    HRS_TXT_R_OP_CLAMP_TO_BORDER,
};

enum HRSPolygonMode {
    HRS_POLYGON_FILL,
    HRS_POLYGON_LINE,
};

typedef struct HRSRenderOptions {
    enum HRSFilter _filter;
    enum HRSTextureRenderOptions _textureRenderOptions;
    enum HRSPolygonMode _polygonMode;
} HRSRenderOptions;

HRSRenderOptions hrsrop_create(enum HRSFilter _filter, enum HRSTextureRenderOptions _textureRenderOptions, enum HRSPolygonMode _polygonMode);

void hrsrop_apply(HRSRenderOptions _renderOptions);

#endif