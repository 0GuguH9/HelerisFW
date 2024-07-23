#include "heleris/fw/graphics/render.h"
#include "heleris/fw/errors/error_presets.h"
#include "heleris/fw/graphics/shader_program.h"

#include <stdlib.h>

// Heap manipulation

HRSRender* hrsr_create(HRSShaderProgram *_shaderProgram, HRSRenderOptions _renderOptions, HRSVAO *_vao, HRSVBO *_vbo){ 

    HRSRender *_render = malloc(sizeof(HRSRender));

    if (_render == nullptr)
        errpre_malloc("HRSRender");

    _render->_shaderProgram = _shaderProgram;
    _render->_renderOptions = _renderOptions;
    _render->_vao = _vao;
    _render->_vbo = _vbo;

    return _render;
}

void hrsr_assert(HRSRender *_render) {

    if (_render == nullptr)
        errpre_nullptr("HRSRender");
}

void hrsr_free(HRSRender *_render) {

    hrsr_assert(_render);

    //hrsvao_free(_render->_vao);
    //hrsvbo_free(_render->_vbo);

    hrsshp_free(_render->_shaderProgram);

    free(_render);
    _render = nullptr;
}

void hrsr_startRender(HRSRender *_render) {

    hrsr_assert(_render);

    hrsshp_active(_render->_shaderProgram);

    //hrsvao_active(_render->_vao);
    //hrsvbo_active(_render->_vbo);
}
