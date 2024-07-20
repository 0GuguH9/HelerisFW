#include "heleris/fw/graphics/shader.h"
#include "heleris/fw/errors/error_presets.h"
#include "heleris/fw/types.h"

#include <stdlib.h>

HRSShader* hrssh_create(const enum EHRSShaderType type, const char *source) {

    HRSShader *shader = malloc(sizeof(HRSShader));

    if (shader == nullptr) {

        errpre_malloc("HRSShader");
    }

    shader->glShader = glCreateShader(type);
    shader->type = type;
    shader->source = source;

    return shader;
}

void hrssh_compile(HRSShader *shader) {

    hrssh_assert(shader);

    if (shader->source == nullptr)
        errpre_nullptr("char *");

    glShaderSource(shader->glShader, 1, &shader->source, (void *)0);
    
    glCompileShader(shader->glShader);

    shader->source = nullptr;
}

void hrssh_assert(const HRSShader *shader) {

    if (shader == nullptr)
        errpre_nullptr("HRSShader");
}

void hrssh_free(HRSShader *shader) {

    hrssh_assert(shader);

    shader->source = nullptr;

    free(shader);
    shader = nullptr;
}
