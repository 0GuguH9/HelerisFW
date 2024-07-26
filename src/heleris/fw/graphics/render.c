#include "heleris/fw/graphics/render.h"
#include "heleris/fw/errors/error_presets.h"
#include "heleris/fw/graphics/render_options.h"
#include "heleris/fw/graphics/shader_program.h"

#include <stdlib.h>

// Heap manipulation

HRSRender* hrsr_create(HRSShaderProgram *_shaderProgram, enum EHRSPolygonMode _polygonMode, HRSVAO *_vao){ 

    HRSRender *_render = malloc(sizeof(HRSRender));

    if (_render == nullptr)
        errpre_malloc("HRSRender");

    _render->_shaderProgram = _shaderProgram;
    _render->_polygonMode = _polygonMode;
    _render->_vao = _vao;

    return _render;
}

void hrsr_assert(HRSRender *_render) {

    if (_render == nullptr)
        errpre_nullptr("HRSRender");
}

void hrsr_free(HRSRender *_render) {

    hrsr_assert(_render);
    hrsvao_free(_render->_vao);
    hrsvbo_free(_render->_vbo);

    hrsshp_free(_render->_shaderProgram);

    free(_render);
    _render = nullptr;
}

// Rendering

void hrsr_start(HRSRender *_render) {

    hrsr_assert(_render);

    hrsshp_bind(_render->_shaderProgram);

    hrsvao_bind(_render->_vao);
    hrsvbo_bind(_render->_vbo);
}

void hrsr_end() {

    hrsshp_unbind();

    hrsvbo_unbind();
    hrsvao_unbind();
}
