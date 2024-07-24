#include "heleris/fw/graphics/shader.h"

#include "heleris/fw/errors/error_codes.h"
#include "heleris/fw/errors/error_presets.h"
#include "heleris/fw/types.h"

#include <stdlib.h>
#include <string.h>

HRSShader* hrssh_create(const enum EHRSShaderType type, const char *source) {

    HRSShader *_shader = malloc(sizeof(HRSShader));

    if (_shader == nullptr) {

        errpre_malloc("HRSShader");
    }

    _shader->glShader = glCreateShader(type);
    _shader->type = type;
    _shader->source = source;

    return _shader;
}

void hrssh_compile(HRSShader *_shader) {

    hrssh_assert(_shader);

    if (_shader->source == nullptr)
        errpre_nullptr("char *");

    glShaderSource(_shader->glShader, 1, &_shader->source, (void *)0);
    
    glCompileShader(_shader->glShader);

    int sucess = 0;
    glGetShaderiv(_shader->glShader, GL_COMPILE_STATUS, &sucess);

    if (!sucess) {
        char infoLog[512];
        glGetShaderInfoLog(_shader->glShader, 512, NULL, infoLog);

        char typeName[32];

        switch(_shader->type) {
            case HRS_GL_SHADER_VERTEX:
                strncpy(typeName, "HRS_GL_SHADER_VERTEX", 21);
            break;
            case HRS_GL_SHADER_FRAGMENT:
                strncpy(typeName, "HRS_GL_SHADER_FRAGMENT", 23);
            break;
            case HRS_GL_SHADER_GEOMETRY:
                strncpy(typeName, "HRS_GL_SHADER_GEOMETRY", 23);
            break;
        }

        HRSError error = {"Shader compile failed", "A OpenGL _shader failed to compile. Bellow this error log has a OpenGL error log", HRS_ERROR_SHADER_FAILED_COMPILATION};
        hrserr_print(&error);
        printf("OpenGL error log:\n Type:%32s\n Log:\n%512s\n", typeName, infoLog);
        exit(HRS_ERROR_SHADER_FAILED_COMPILATION);
    }

    _shader->source = nullptr;
}

void hrssh_assert(const HRSShader *_shader) {

    if (_shader == nullptr)
        errpre_nullptr("HRSShader");
}

void hrssh_free(HRSShader *_shader) {

    hrssh_assert(_shader);

    _shader->source = nullptr;

    glDeleteShader(_shader->glShader);

    free(_shader);
    _shader = nullptr;
}
