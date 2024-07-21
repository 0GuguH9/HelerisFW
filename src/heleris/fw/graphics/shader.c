#include "heleris/fw/graphics/shader.h"

#include "heleris/fw/errors/error_codes.h"
#include "heleris/fw/errors/error_presets.h"
#include "heleris/fw/types.h"

#include <stdlib.h>
#include <string.h>

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

    int sucess = 0;
    glGetShaderiv(shader->glShader, GL_COMPILE_STATUS, &sucess);

    if (!sucess) {
        char infoLog[512];
        glGetShaderInfoLog(shader->glShader, 512, NULL, infoLog);

        char typeName[32];

        switch(shader->type) {
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

        HRSError error = {"Shader compile failed", "A OpenGL shader failed to compile. Bellow this error log has a OpenGL error log", HRS_ERROR_SHADER_FAILED_COMPILATION};
        hrserr_print(&error);
        printf("OpenGL error log:\n Type:%32s\n Log:\n%512s\n", typeName, infoLog);
        exit(HRS_ERROR_SHADER_FAILED_COMPILATION);
    }

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
