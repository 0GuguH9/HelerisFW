#include "heleris/fw/gl_context.h"

#include "heleris/fw/errors/error.h"
#include "heleris/fw/errors/error_codes.h"
#include "heleris/fw/errors/error_presets.h"
#include "heleris/fw/window.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>

// Private fields:

void hrsglc_glfwResizeCallback(GLFWwindow *window, int width, int height) {

    HRSWindow* hrsWindow = (HRSWindow*)glfwGetWindowUserPointer(window);

    if (hrsWindow != nullptr && hrsWindow->onWindowResize != nullptr) {

        HRSSize2 newSize = { width, height };
        hrsWindow->onWindowResize(hrsWindow, newSize);
    }
}

// Plublic fields:

HRSGLContext* hrsglc_create(enum EHRSMajorVersion majorVersion, int minorVersion, enum EHRSProfileType profileType) {

    HRSGLContext *context = malloc(sizeof(HRSGLContext));

    if (context == nullptr) 
        errpre_malloc("HRSGLContext");

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

    if (context == nullptr)
        errpre_nullptr("HRSGLContext");

    if (context->hasBeenInitialized) {

        HRSError error = {"attempt to reinitialize GLFW and GLAD", "there was an attempt to reset GLFW and GLAD, which may cause errors."
            " \nAvoid having more than one object of type \"HRSGLContext\"", HRS_ERROR_HRSGLC_ALREADY_INITIALIZED};
        hrserr_printAndStopProgram(&error);
    }

    if (!glfwInit()) {

        HRSError error = {"GLFW can't init", "unable to start GLFW, check your operating system", HRS_ERROR_GLFW_CANT_INIT};
        hrserr_printAndStopProgram(&error);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context->majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context->minorVersion);

    glfwWindowHint(GLFW_OPENGL_PROFILE, context->profileType);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        HRSError error = {"GLAD can't init", "GLAD can't get the correct address of OpenGL functions", HRS_ERROR_GLAD_CANT_FINT_IMPLEMENTATIONS};
        hrserr_printAndStopProgram(&error);
    }

    context->hasBeenInitialized = TRUE;
}

void hrsglc_useWindow(HRSGLContext *context, HRSWindow *window) {

    hrsglc_assertIsAlreadyInitialized(context);

    hrswin_assertWindowInstNull(window);

    context->currentWindow = window;

    glfwMakeContextCurrent(context->currentWindow->glfwWindow); // Rust ownership concept :D

    glfwSetWindowUserPointer(window->glfwWindow, window);

    glfwSetFramebufferSizeCallback(window->glfwWindow, hrsglc_glfwResizeCallback);
}

void hrsglc_registerUpdateCallback(HRSGLContext *context, void (*onUpdate)(double deltaTime)) {

    hrsglc_assertIsAlreadyInitialized(context);

    if (onUpdate == nullptr)
        errpre_nullptr("void (*onUpdate)(double deltaTime)");

    context->onUpdate = onUpdate;
}

void hrsglc_registerDrawCallback(HRSGLContext *context, void (*onDraw)()) {

    hrsglc_assertIsAlreadyInitialized(context);

    if (onDraw == nullptr)
        errpre_nullptr("void (*onDraw)()");

    context->onDraw = onDraw;
}

void hrsglc_cycleCooldown(HRSGLContext *context, double cooldown) {

    hrsglc_assertIsAlreadyInitialized(context);

    context->swapCooldown = (int)(cooldown * 1000.0);
}

void hrsglc_vSync(HRSGLContext *context, bool_t newState) {

    hrsglc_assertIsAlreadyInitialized(context);

    glfwSwapInterval(newState);
}

void hrsglc_startLoop(HRSGLContext *context) {

    hrsglc_assertIsAlreadyInitialized(context);

    double previousTime = glfwGetTime();
    double currentTime;
    double deltaTime;
    double fpsTimer = 0.0;
    int frameCount = 0;

    if (context->currentWindow == nullptr)
        errpre_nullptr("HRSWindow");

    while(!glfwWindowShouldClose(context->currentWindow->glfwWindow)) {

        if (context->swapCooldown > 0) {

            double currentSwapTime = glfwGetTime();
            double swapDeltaTime = currentSwapTime - previousTime;

            if (context->swapCooldown / 1000.0 > swapDeltaTime)
                continue;
        }

        currentTime = glfwGetTime();
        deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        fpsTimer += deltaTime;
        frameCount++;

        if (fpsTimer >= 1.0) {

            context->fps = frameCount / fpsTimer;
            fpsTimer = 0.0;
            frameCount = 0;
        }

        context->estimatedFPS = 1.0 / deltaTime;

        glClearColor(hrsclr_toFloat(context->currentWindow->backgroundColor, HRS_COLOR_RGBA_R),
            hrsclr_toFloat(context->currentWindow->backgroundColor, HRS_COLOR_RGBA_G),
            hrsclr_toFloat(context->currentWindow->backgroundColor, HRS_COLOR_RGBA_B),
            hrsclr_toFloat(context->currentWindow->backgroundColor, HRS_COLOR_RGBA_A));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (context->onUpdate != nullptr)
            context->onUpdate(deltaTime);

        if (context->onDraw != nullptr)
            context->onDraw();

        hrsglc_swapBuffers(context);

        glfwPollEvents();
    }
}

void hrsglc_closeLoop(HRSGLContext *context) {

    hrsglc_assertIsAlreadyInitialized(context);

    glfwSetWindowShouldClose(context->currentWindow->glfwWindow, GLFW_TRUE);
    
    hrswin_assertWindowInstNull(context->currentWindow);

    if (context->currentWindow->onWindowClose != nullptr)
        context->currentWindow->onWindowClose(context->currentWindow);
}

void hrsglc_swapBuffers(HRSGLContext *context) {

    hrsglc_assertIsAlreadyInitialized(context);

    glfwSwapBuffers(context->currentWindow->glfwWindow);
}

void hrsglc_assertIsAlreadyInitialized(HRSGLContext *context) {
    
    if (context == nullptr) 
        errpre_nullptr("HRSGLContext");

    if (!context->hasBeenInitialized) {

        HRSError error = {"GLFW and GLAD not initialized", "attempt to use an object of type HRSGLContext without initializing GLAD or GLFW", HRS_ERROR_GLAD_CANT_FINT_IMPLEMENTATIONS};
        hrserr_printAndStopProgram(&error);
    }
}

void hrsglc_terminate(HRSGLContext *context) {

    hrsglc_assertIsAlreadyInitialized(context);

    hrswin_free(context->currentWindow);
    free(context);

    glfwTerminate();

    context = nullptr;
}
