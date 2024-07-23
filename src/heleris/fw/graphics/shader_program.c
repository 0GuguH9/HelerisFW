#include "heleris/fw/graphics/shader_program.h"

#include "heleris/fw/errors/error_codes.h"
#include "heleris/fw/errors/error_presets.h"
#include "heleris/fw/graphics/shader.h"

#include <stdlib.h>

HRSShaderProgram* hrsshp_create() {

    HRSShaderProgram *program = malloc(sizeof(HRSShaderProgram));

    if (program == nullptr)
        errpre_malloc("HRSShaderProgram");

    program->glShaderProgram = glCreateProgram();

    return program;
}

void hrsshp_assert(HRSShaderProgram *program) {

    if (program == nullptr)
        errpre_nullptr("HRSShaderProgram");

    glValidateProgram(program->glShaderProgram);
}

void hrsshp_free(HRSShaderProgram *program) {

    free(program);
    program = nullptr;
}

void hrsshp_attach(HRSShaderProgram *program, HRSShader *shader) {

    hrsshp_assert(program);

    glAttachShader(program->glShaderProgram, shader->glShader);
}

void hrsshp_link(HRSShaderProgram *program) {

    hrsshp_assert(program);

    glLinkProgram(program->glShaderProgram);

    int success;
    glGetProgramiv(program->glShaderProgram, GL_LINK_STATUS, &success);

    if(!success) {

        char infoLog[512];
        glGetProgramInfoLog(program->glShaderProgram, 512, NULL, infoLog);

        HRSError error = {"Shader Program linkation failed", "A OpenGL Shader Program failed in linkation process. Bellow this error log has a OpenGL error log", HRS_ERROR_SHPROGRAM_FAILED_LINK};
        hrserr_print(&error);
        printf("OpenGL error log:\nLog:\n%512s\n", infoLog);
        exit(HRS_ERROR_SHPROGRAM_FAILED_LINK);
    }
}

void hrsshp_active(HRSShaderProgram *program) {

    hrsshp_assert(program);

    glUseProgram(program->glShaderProgram);
}
