#include "headers/gl_context.h"

#include "headers/error_codes.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>

HRSGLContext* hrsglc_create(enum EHRSMajorVersion majorVersion, int minorVersion, enum EHRSProfileType profileType) {

    HRSGLContext *context = malloc(sizeof(HRSGLContext));

    if (context == nullptr) {
        fprintf(stderr, "[HRSGLContext]: can't alloc memory for a context");
        exit(HRS_ERROR_MALLOC_ERROR);
    }

    context->majorVersion = majorVersion;
    context->minorVersion = minorVersion;
    context->profileType = profileType;
    context->hasBeenInitialized = FALSE;
    context->useVSync = FALSE;
    context->swapCooldown = 0; // No cooldown
    context->fps = 0;
    context->currentWindow = nullptr;
    context->onDraw = nullptr;
    context->onUpdate = nullptr;

    return context;
}

void hrsglc_init(HRSGLContext *context) {

    if (context == nullptr) {

        fprintf(stderr, "[HRSGLContext]: attempting to use a NULL context");
        exit(HRS_ERROR_TRY_TO_USE_NULL);
    }

    if (context->hasBeenInitialized) {

        fprintf(stderr, "[HRSGLContext]: attempt to reinitialize GLFW and GLAD");
        exit(HRS_ERROR_HRSGLC_ALREADY_INITIALIZED);
    }

    if (!glfwInit()) {

        fprintf(stderr, "[HRSGLContext]: GLFW can't init");
        exit(HRS_ERROR_GLFW_CANT_INIT);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context->majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context->minorVersion);

    glfwWindowHint(GLFW_OPENGL_PROFILE, context->profileType);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        fprintf(stderr, "[HRSGLContext]: GLAD can't get the correct address of OpenGL functions");
        exit(HRS_ERROR_GLAD_CANT_FINT_IMPLEMENTATIONS);
    }

    context->hasBeenInitialized = TRUE;
}

void hrsglc_useWindow(HRSGLContext *context, HRSWindow *window) {

    hrsglc_assertIsAlredyInitialized(context);

    context->currentWindow = window;

    glfwMakeContextCurrent(context->currentWindow->glfwWindow); // Rust ownership concept :D
}

void hrsglc_registerUpdateCallback(HRSGLContext *context, void (*onUpdate)(double deltaTime)) {

    hrsglc_assertIsAlredyInitialized(context);

    context->onUpdate = onUpdate;
}

void hrsglc_cycleCooldown(HRSGLContext *context, double cooldown) {

    hrsglc_assertIsAlredyInitialized(context);

    context->swapCooldown = (int)(cooldown * 1000.0);
}

void hrsglc_vSync(HRSGLContext *context, bool_t newState) {

    hrsglc_assertIsAlredyInitialized(context);

    glfwSwapInterval(newState);
}

void hrsglc_startLoop(HRSGLContext *context) {

    hrsglc_assertIsAlredyInitialized(context);

    double previousTime = glfwGetTime();
    double currentTime;
    double deltaTime;

    while(!glfwWindowShouldClose(context->currentWindow->glfwWindow)) {

        currentTime = glfwGetTime();
        deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        if (context->onUpdate != nullptr)
            context->onUpdate(deltaTime);

        if (context->onDraw != nullptr)
            context->onDraw();

        hrsglc_swapBuffers(context);

        glfwPollEvents();
    }
}

void hrsglc_closeLoop(HRSGLContext *context) {

    hrsglc_assertIsAlredyInitialized(context);

    glfwSetWindowShouldClose(context->currentWindow->glfwWindow, TRUE);
}

void hrsglc_swapBuffers(HRSGLContext *context) {

    hrsglc_assertIsAlredyInitialized(context);

    glfwSwapBuffers(context->currentWindow->glfwWindow);
}

void hrsglc_registerDrawCallback(HRSGLContext *context, void (*onDraw)()) {

    hrsglc_assertIsAlredyInitialized(context);

    context->onDraw = onDraw;
}

void hrsglc_assertIsAlredyInitialized(HRSGLContext *context) {
    
    if (context == nullptr) {

        fprintf(stderr, "[HRSGLContext]: attempting to use a NULL context");
        exit(HRS_ERROR_TRY_TO_USE_NULL);
    }

    if (!context->hasBeenInitialized) {

        fprintf(stderr, "[HRSGLContext]: GLFW and GLAD not initialized");
        exit(HRS_ERROR_HRSGLC_NOT_INITIALIZED);
    }
}

void hrsglc_terminate(HRSGLContext *context) {

    hrsglc_assertIsAlredyInitialized(context);

    hrswin_free(context->currentWindow);
    free(context);

    glfwTerminate();

    context = nullptr;
}
